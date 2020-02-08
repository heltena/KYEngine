#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/PathAllAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

const std::string PathAllAction::XML_NODE = "path-all";

PathAllAction::PathAllAction()
{
}

PathAllAction::~PathAllAction()
{
}

PathAllAction* PathAllAction::readFromXml(TiXmlElement* node)
{
	PathAllAction* action = new PathAllAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	double duration = TiXmlHelper::readDouble(node, "duration", true);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);

	action->setName(name);
	action->setDuration(duration);
	action->setEntityRef(entityRef);

    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == "ref-point") {
            const Vector4 refPositionPoint = TiXmlHelper::readVector(curr, "x", "y", "z", "", READ_X | READ_Y, 0, 0, 0, 0);
            action->addRefPoint(refPositionPoint);
            const Vector4 refScalePoint = TiXmlHelper::readVector(curr, "sx", "sy", "sz", "", READ_X | READ_Y, 1, 1, 1, 0);
            action->addRefScalePoint(refScalePoint);
        } else
			throw std::runtime_error("PathAllAction ref-point: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
            
	return action;
}

void PathAllAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_duration == 0) {
        m_entity->setPos(m_refPositionPoints.back());
        m_entity->setScale(m_refScalePoints.back());
    } else {
        m_entity->setPos(m_refPositionPoints.front());
        m_entity->setScale(m_refScalePoints.front());
    }
	m_elapsedTime = 0;
    
    int size = m_refPositionPoints.size();
    
    m_durations.clear();
    m_durations.resize(size);

    float length = 0;
    Vector4 curr = m_refPositionPoints[0];
    m_durations[0] = 0;
    for(int  i = 1; i < size; i++) {
        length += (m_refPositionPoints[i] - curr).len();
        m_durations[i] = length;
        curr = m_refPositionPoints[i];
    }
    for(int i = 0; i < size; i++)
        m_durations[i] /= length;
    
    m_curSegment = 1;
}

void PathAllAction::stop(SceneTimelineInfo* info)
{
	m_entity->setPos(m_refPositionPoints.back());
	m_entity->setScale(m_refScalePoints.back());
}

bool PathAllAction::isBlocking()
{
	return false;
}

bool PathAllAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void PathAllAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_duration == 0)
        return;
	m_elapsedTime += elapsedTime;

    double t = m_elapsedTime / m_duration;
    
    while (m_curSegment < m_durations.size() && m_durations[m_curSegment] < t)
        m_curSegment++;
    
    double tt = (t - m_durations[m_curSegment-1]) / (m_durations[m_curSegment] - m_durations[m_curSegment-1]);
    
    Vector4 newPos = Vector4::interpolate(m_refPositionPoints[m_curSegment-1], m_refPositionPoints[m_curSegment], tt);
    Vector4 newScale = Vector4::interpolate(m_refScalePoints[m_curSegment-1], m_refScalePoints[m_curSegment], tt);
    
    m_entity->setPos(newPos);
    m_entity->setScale(newScale);
}
