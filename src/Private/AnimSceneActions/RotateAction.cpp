#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Private/AnimSceneActions/RotateAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string RotateAction::XML_NODE = "rotate";

RotateAction::RotateAction()
{
}

RotateAction::~RotateAction()
{
}

RotateAction* RotateAction::readFromXml(TiXmlElement* node)
{
	RotateAction* action = new RotateAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    
    bool loop = TiXmlHelper::readBool(node, "loop", false, false);
    double celerity = 0;
    double duration = 0;
    bool fromCurrentAngle = false;
    double from = 0;
    double to = 0;
    double accelMagnitude = 0;
    
    if (loop)
        celerity = TiXmlHelper::readDouble(node, "celerity", true);
    else {
        duration = TiXmlHelper::readDouble(node, "duration", true);
        fromCurrentAngle = TiXmlHelper::readBool(node, "from-current-angle", false, false);
        if (!fromCurrentAngle)
            from = TiXmlHelper::readDouble(node, "from", true);
        to = TiXmlHelper::readDouble(node, "to", true);
        accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", false, 0.0);
	}

	action->setName(name);
	action->setEntityRef(entityRef);
    action->setLoop(loop);
    action->setCelerity(celerity);
	action->setDuration(duration);
    action->setFromCurrentAngle(fromCurrentAngle);
	action->setFrom(from);
	action->setTo(to);
	action->setAccelMagnitude(accelMagnitude);
	
	return action;
}

void RotateAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (! m_loop) {
        if (m_duration == 0)
            m_entity->setAngle(m_to);
        else if (m_fromCurrentAngle)
            m_from = m_entity->angle();
        else
            m_entity->setAngle(m_from);
    }
	m_elapsedTime = 0;
}

bool RotateAction::isBlocking()
{
	return false;
}

bool RotateAction::isFinished()
{
	return !m_loop && m_elapsedTime >= m_duration;
}

void RotateAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    double newAngle;
    if (m_loop)
        newAngle = m_entity->angle() + elapsedTime * m_celerity;
    else {
        if (m_duration == 0)
            return;
        m_elapsedTime += elapsedTime;
        newAngle = Math::interpolate(m_from, m_to, m_elapsedTime / m_duration, m_accelMagnitude);
    }
    m_entity->setAngle(newAngle);
}
