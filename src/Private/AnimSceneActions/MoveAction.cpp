#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/MoveAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string MoveAction::XML_NODE = "move";

MoveAction::MoveAction()
{
}

MoveAction::~MoveAction()
{
}

MoveAction* MoveAction::readFromXml(TiXmlElement* node)
{
	MoveAction* action = new MoveAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    int times = TiXmlHelper::readInt(node, "times", false, 1);
    bool useCelerity = TiXmlHelper::containsAttribute(node, "celerity");
    double duration = !useCelerity ? TiXmlHelper::readDouble(node, "duration", true) : 0;
    double celerity = useCelerity ? TiXmlHelper::readDouble(node, "celerity", true) : 0;
    bool loop = TiXmlHelper::readBool(node, "loop", false, false);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    bool fromCurrentPos = TiXmlHelper::readBool(node, "from-current-pos", false, false);
	Vector4 from;
    if (!fromCurrentPos)
        from = TiXmlHelper::readVector(node, "fx", "fy", "fz", "", READ_X | READ_Y | READ_Z);
	const Vector4 to = TiXmlHelper::readVector(node, "tx", "ty", "tz", "", READ_X | READ_Y | READ_Z);
	double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", false, 0.0);
	
	action->setName(name);
    action->setTimes(times);
    action->setUseCelerity(useCelerity);
	action->setDuration(duration);
    action->setCelerity(celerity);
    action->setLoop(loop);
	action->setEntityRef(entityRef);
    action->setFromCurrentPos(fromCurrentPos);
	action->setFrom(from);
	action->setTo(to);
	action->setAccelMagnitude(accelMagnitude);
	
	return action;
}

void MoveAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_useCelerity) {
        if (m_fromCurrentPos)
            m_from = m_entity->pos();
        m_duration = (m_to - m_from).len() / m_celerity;
    }
    
    if (m_duration == 0)
        m_entity->setPos(m_to);
    else if (m_fromCurrentPos)
        m_from = m_entity->pos();
    else
        m_entity->setPos(m_from);
	m_elapsedTime = 0;
}

bool MoveAction::isBlocking()
{
	return false;
}

bool MoveAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void MoveAction::update(const double elapsedTime, SceneTimelineInfo* info)
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
	Vector4 newPos = Vector4::interpolate(m_from, m_to, value, m_accelMagnitude);
    m_entity->setPos(newPos);
}
