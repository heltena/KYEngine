#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/ChangeColorAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string ChangeColorAction::XML_NODE = "change-color";

ChangeColorAction::ChangeColorAction()
{
}

ChangeColorAction::~ChangeColorAction()
{
}

ChangeColorAction* ChangeColorAction::readFromXml(TiXmlElement* node)
{
	ChangeColorAction* action = new ChangeColorAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	double duration = TiXmlHelper::readDouble(node, "duration", true);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    bool fromCurrentColor = TiXmlHelper::readBool(node, "from-current-color", false, false);
	Vector4 from;
    if (!fromCurrentColor)
        from = TiXmlHelper::readVector(node, "fr", "fg", "fb", "fa", READ_X | READ_Y | READ_Z | READ_W);
	const Vector4 to = TiXmlHelper::readVector(node, "tr", "tg", "tb", "ta", READ_X | READ_Y | READ_Z | READ_W);
	double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", false, 0.0);
	
	action->setName(name);
	action->setDuration(duration);
	action->setEntityRef(entityRef);
    action->setFromCurrentColor(fromCurrentColor);
	action->setFrom(from);
	action->setTo(to);
	action->setAccelMagnitude(accelMagnitude);
	
	return action;
}

void ChangeColorAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    if (m_fromCurrentColor)
        m_from = m_entity->color();
    else
        m_entity->setColor(m_from);
	m_elapsedTime = 0;
}

bool ChangeColorAction::isBlocking()
{
	return false;
}

bool ChangeColorAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void ChangeColorAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
	m_elapsedTime += elapsedTime;
	Vector4 newColor = Vector4::interpolate(m_from, m_to, m_elapsedTime / m_duration, m_accelMagnitude);
	m_entity->setColor(newColor);
}
