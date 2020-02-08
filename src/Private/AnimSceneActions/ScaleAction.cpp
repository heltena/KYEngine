#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/ScaleAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string ScaleAction::XML_NODE = "scale";

ScaleAction::ScaleAction()
{
}

ScaleAction::~ScaleAction()
{
}

ScaleAction* ScaleAction::readFromXml(TiXmlElement* node)
{
	ScaleAction* action = new ScaleAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    int times = TiXmlHelper::readInt(node, "times", false, 1);
	double duration = TiXmlHelper::readDouble(node, "duration", true);
    bool loop = TiXmlHelper::readBool(node, "loop", false, false);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    bool fromCurrentScale = TiXmlHelper::readBool(node, "from-current-scale", false, false);
	Vector4 from;
    if (!fromCurrentScale)
        from = TiXmlHelper::readVector(node, "fx", "fy", "fz", "", READ_X | READ_Y | READ_Z);
	const Vector4 to = TiXmlHelper::readVector(node, "tx", "ty", "tz", "", READ_X | READ_Y | READ_Z);
	double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", false, 0.0);
	
	action->setName(name);
    action->setTimes(times);
	action->setDuration(duration);
    action->setLoop(loop);
	action->setEntityRef(entityRef);
    action->setFromCurrentScale(fromCurrentScale);
	action->setFrom(from);
	action->setTo(to);
	action->setAccelMagnitude(accelMagnitude);
	
	return action;
}

void ScaleAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_duration == 0)
        m_entity->setScale(m_to);
    else if (m_fromCurrentScale)
        m_from = m_entity->scale();
    else
        m_entity->setScale(m_from);
	m_elapsedTime = 0;
}

bool ScaleAction::isBlocking()
{
	return false;
}

bool ScaleAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void ScaleAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_duration == 0)
        return;
	m_elapsedTime += elapsedTime;
    double value = m_elapsedTime * m_times / m_duration;
    if (m_times > 1 || m_loop) {
        double intpart;
        value = modf(value * m_times * (m_loop ? 2 : 1), &intpart);
        if (((int) intpart) % 2 == 1)
            value = 1 - value;
    }
	Vector4 newScale = Vector4::interpolate(m_from, m_to, value, m_accelMagnitude);
    m_entity->setScale(newScale);
}
