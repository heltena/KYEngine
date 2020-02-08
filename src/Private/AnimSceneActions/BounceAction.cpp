#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Private/AnimSceneActions/BounceAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string BounceAction::XML_NODE = "bounce";

BounceAction::BounceAction()
{
}

BounceAction::~BounceAction()
{
}

BounceAction* BounceAction::readFromXml(TiXmlElement* node)
{
	BounceAction* action = new BounceAction();
	
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

void BounceAction::start(SceneTimelineInfo* info)
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

bool BounceAction::isBlocking()
{
	return false;
}

bool BounceAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void BounceAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_duration == 0)
        return;
	m_elapsedTime += elapsedTime;
    double value = m_elapsedTime / m_duration;
    double angle = value * (m_steps * M_PI);
    double height = Math::abs(Math::sin(angle)) * m_amplitude;
	Vector4 newPos = Vector4::interpolate(m_from, m_to, value, 1);
    newPos[1] += height;
    m_entity->setPos(newPos);
}
