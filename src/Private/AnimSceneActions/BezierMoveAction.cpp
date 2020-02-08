#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/BezierMoveAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

const std::string BezierMoveAction::XML_NODE = "bezier-move";

BezierMoveAction::BezierMoveAction()
{
}

BezierMoveAction::~BezierMoveAction()
{
}

BezierMoveAction* BezierMoveAction::readFromXml(TiXmlElement* node)
{
	BezierMoveAction* action = new BezierMoveAction();
	
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
			throw std::runtime_error("BezierMoveAction ref-point: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
            
	return action;
}

void BezierMoveAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_duration == 0)
        m_entity->setPos(m_refPoints.back());
    else
        m_entity->setPos(m_refPoints.front());
	m_elapsedTime = 0;
    
    int size = m_refPoints.size();

    m_combs.clear();
    m_combs.resize(size);

    float fn = 1.0f;
    for(int i = 2; i < size; i++)
        fn *= i;
        
    float fi = 1.0f;
    float fni = fn;
    for(int i = 0; i < size; i++) {
        m_combs[i] = fn / (fi * fni);
        fi *= (i + 1);
        if (i != size - 1)
            fni /= (size - i - 1);
    }
}

bool BezierMoveAction::isBlocking()
{
	return false;
}

bool BezierMoveAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void BezierMoveAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_duration == 0)
        return;
	m_elapsedTime += elapsedTime;

    double t = m_elapsedTime / m_duration;
    
    const int size = m_refPoints.size();
    double powti = 1;
    double pow1tsi = pow(1-t, size - 1);
    Vector4 result;
    for(int i = 0; i < size; i++) {
        float b = m_combs[i];
        if (i != 0)
            b *= powti;
        if (i != size - 1)
            b *= pow1tsi;
            
        powti *= t;
        if (t != 1)
            pow1tsi /= (1-t);
        
        result += m_refPoints[i] * b;
    }
	m_entity->setPos(result);
    
/* Lo que estaba antes
    Vector4 result;
    const int size = m_refPoints.size();
    for(int i = 0; i < size; i++) {
        float b = m_combs[i];
        if (i != 0)
            b *= pow(t, i);
        if (i != size - 1)
            b *= pow(1-t, size - i - 1);
        
        result += m_refPoints[i] * b;
    }
	m_entity->setPos(result);
*/}
