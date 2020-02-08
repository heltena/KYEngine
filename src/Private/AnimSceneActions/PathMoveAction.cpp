#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/PathMoveAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

const std::string PathMoveAction::XML_NODE = "path-move";

PathMoveAction::PathMoveAction()
{
}

PathMoveAction::~PathMoveAction()
{
}

PathMoveAction* PathMoveAction::readFromXml(TiXmlElement* node)
{
	PathMoveAction* action = new PathMoveAction();
	
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
            const Vector4 refPoint = TiXmlHelper::readVector(curr, "x", "y", "z", "", READ_X | READ_Y, 0, 0, 0, 0);
            action->addRefPoint(refPoint);
        } else
			throw std::runtime_error("PathMoveAction ref-point: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
            
	return action;
}

void PathMoveAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_duration == 0)
        m_entity->setPos(m_refPoints.back());
    else
        m_entity->setPos(m_refPoints.front());
	m_elapsedTime = 0;
    
    int size = m_refPoints.size();

    m_durations.clear();
    m_durations.resize(size-1);

    float length = 0;
    Vector4 curr = m_refPoints[0];
    for(int  i = 1; i < size; i++) {
        length += (m_refPoints[i] - curr).len();
        m_durations[i-1] = length;
        curr = m_refPoints[i];
    }
    for(int i = 0; i < size - 1; i++)
        m_durations[i] /= length;
    m_curSegment = 0;
}

bool PathMoveAction::isBlocking()
{
	return false;
}

bool PathMoveAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void PathMoveAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_duration == 0)
        return;
	m_elapsedTime += elapsedTime;

    double t = m_elapsedTime / m_duration;
    
    while (m_curSegment < m_durations.size() && m_durations[m_curSegment+1] < t)
        m_curSegment++;
    
    Vector4 result;
    if (m_curSegment == m_durations.size())
        result = m_refPoints.back();
    else {
        double tt = (t - m_durations[m_curSegment]) / (m_durations[m_curSegment+1] - m_durations[m_curSegment]);
        result = Vector4::interpolate(m_refPoints[m_curSegment], m_refPoints[m_curSegment+1], tt);
    }
	m_entity->setPos(result);
}
