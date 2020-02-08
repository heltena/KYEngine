#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/RemoveEntityAction.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string RemoveEntityAction::XML_NODE = "remove-entity";

RemoveEntityAction::RemoveEntityAction()
{
}

RemoveEntityAction::~RemoveEntityAction()
{
}

RemoveEntityAction* RemoveEntityAction::readFromXml(TiXmlElement* node)
{
	RemoveEntityAction* action = new RemoveEntityAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	
	action->setName(name);
	action->setEntityRef(entityRef);
	
	return action;
}

void RemoveEntityAction::start(SceneTimelineInfo* info)
{
	Entity* entity = Core::resourceManager().entity(m_entityRef);
	info->layer()->removeEntity(entity);
}

bool RemoveEntityAction::isBlocking()
{
	return false;
}

bool RemoveEntityAction::isFinished()
{
	return true;
}

void RemoveEntityAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
