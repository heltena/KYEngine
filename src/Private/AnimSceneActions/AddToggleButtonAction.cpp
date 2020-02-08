#include <KYEngine/Private/AnimSceneActions/AddToggleButtonAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string AddToggleButtonAction::XML_NODE = "add-toggle-button-event";

AddToggleButtonAction::AddToggleButtonAction()
{
}

AddToggleButtonAction::~AddToggleButtonAction()
{
}

AddToggleButtonAction* AddToggleButtonAction::readFromXml(TiXmlElement* node)
{
	AddToggleButtonAction* action = new AddToggleButtonAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	const std::string offAnimRef = TiXmlHelper::readString(node, "off-anim-ref", true);
	const std::string onAnimRef = TiXmlHelper::readString(node, "on-anim-ref", true);
    const std::string initValue = TiXmlHelper::readString(node, "init-value", true);
	const std::string toOffScript = TiXmlHelper::readString(node, "to-off-script", true);
	const std::string toOnScript = TiXmlHelper::readString(node, "to-on-script", true);
    
	action->setName(name);
	action->setEntityRef(entityRef);
    action->setOffAnimRef(offAnimRef);
    action->setOnAnimRef(onAnimRef);
    action->setInitValue(initValue);
    action->setToOffScript(toOffScript);
    action->setToOnScript(toOnScript);
    
	return action;
}

void AddToggleButtonAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    m_isActive = info->executeEL(m_initValue) == "true";
    m_entity->setAnim(m_isActive ? m_onAnimRef : m_offAnimRef);
	info->addToggleButtonEvent(this);
}

bool AddToggleButtonAction::isBlocking()
{
	return false;
}

bool AddToggleButtonAction::isFinished()
{
	return false;
}

void AddToggleButtonAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}

bool AddToggleButtonAction::isActive(SceneTimelineInfo* info) const
{
    return m_isActive;
}

void AddToggleButtonAction::setOn(SceneTimelineInfo* info)
{
    m_isActive = true;
    m_entity->setAnim(m_onAnimRef);
    info->executeEL(m_toOnScript);
}

void AddToggleButtonAction::setOff(SceneTimelineInfo* info)
{
    m_isActive = false;
    m_entity->setAnim(m_offAnimRef);
    info->executeEL(m_toOffScript);
}

