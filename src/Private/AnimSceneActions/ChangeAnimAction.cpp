#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/ChangeAnimAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string ChangeAnimAction::XML_NODE = "change-anim";

ChangeAnimAction::ChangeAnimAction()
{
}

ChangeAnimAction::~ChangeAnimAction()
{
}

ChangeAnimAction* ChangeAnimAction::readFromXml(TiXmlElement* node)
{
	ChangeAnimAction* action = new ChangeAnimAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	const std::string animRef = TiXmlHelper::readString(node, "anim-ref", true);
	
	action->setName(name);
	action->setEntityRef(entityRef);
	action->setAnimRef(animRef);
	
	return action;
}

void ChangeAnimAction::start(SceneTimelineInfo* info)
{
	Entity* entity = Core::resourceManager().entity(m_entityRef);
	entity->setAnim(m_animRef);
}

bool ChangeAnimAction::isBlocking()
{
	return false;
}

bool ChangeAnimAction::isFinished()
{
	return true;
}

void ChangeAnimAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
