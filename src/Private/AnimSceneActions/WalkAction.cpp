#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Private/AnimSceneActions/WalkAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string WalkAction::XML_NODE = "walk";

WalkAction::WalkAction()
{
}

WalkAction::~WalkAction()
{
}

WalkAction* WalkAction::readFromXml(TiXmlElement* node)
{
	WalkAction* action = new WalkAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    double steps = TiXmlHelper::readDouble(node, "steps", true);
    double amplitude = TiXmlHelper::readDouble(node, "amplitude", true);
    double duration = TiXmlHelper::readDouble(node, "duration", true);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    bool fromCurrentPos = TiXmlHelper::readBool(node, "from-current-pos", false, false);
	Vector4 from;
    if (!fromCurrentPos)
        from = TiXmlHelper::readVector(node, "fx", "fy", "fz", "", READ_X | READ_Y | READ_Z);
	const Vector4 to = TiXmlHelper::readVector(node, "tx", "ty", "tz", "", READ_X | READ_Y | READ_Z);
	
	action->setName(name);
    action->setSteps(steps);
    action->setAmplitude(amplitude);
    action->setDuration(duration);
	action->setEntityRef(entityRef);
    action->setFromCurrentPos(fromCurrentPos);
	action->setFrom(from);
	action->setTo(to);
	
	return action;
}

void WalkAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_fromCurrentPos)
        m_from = m_entity->pos();
    
    if (m_duration == 0)
        m_entity->setPos(m_to);
    else if (m_fromCurrentPos)
        m_from = m_entity->pos();
    else
        m_entity->setPos(m_from);
	m_elapsedTime = 0;
}

bool WalkAction::isBlocking()
{
	return false;
}

bool WalkAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void WalkAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_duration == 0)
        return;
	m_elapsedTime += elapsedTime;
    if (m_elapsedTime > m_duration)
        m_elapsedTime = m_duration;
    double value = m_elapsedTime / m_duration;
    
    double halfStepDuration = m_duration / (m_steps * 2);
    int curHalfStep = (int) (m_elapsedTime / halfStepDuration);
    double offset = m_elapsedTime - curHalfStep * halfStepDuration;
    
    Vector4 newPos = Vector4::interpolate(m_from, m_to, value, 1);
    if (curHalfStep % 2 == 0)
        newPos[1] += offset / halfStepDuration * m_amplitude;
    else
        newPos[1] += (halfStepDuration - offset) / halfStepDuration * m_amplitude;
    m_entity->setPos(newPos);
}
