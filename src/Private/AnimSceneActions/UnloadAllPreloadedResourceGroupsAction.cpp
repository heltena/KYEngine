#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/UnloadAllPreloadedResourceGroupsAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string UnloadAllPreloadedResourceGroupsAction::XML_NODE = "unload-all-preloaded-resource-groups";

UnloadAllPreloadedResourceGroupsAction::UnloadAllPreloadedResourceGroupsAction()
{
}

UnloadAllPreloadedResourceGroupsAction::~UnloadAllPreloadedResourceGroupsAction()
{
}

UnloadAllPreloadedResourceGroupsAction* UnloadAllPreloadedResourceGroupsAction::readFromXml(TiXmlElement* node)
{
	UnloadAllPreloadedResourceGroupsAction* action = new UnloadAllPreloadedResourceGroupsAction();
    
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void UnloadAllPreloadedResourceGroupsAction::start(SceneTimelineInfo* info)
{
    Core::resourceManager().unloadAllPreloadedResourceGroups();
}

bool UnloadAllPreloadedResourceGroupsAction::isBlocking()
{
	return false;
}

bool UnloadAllPreloadedResourceGroupsAction::isFinished()
{
	return true;
}

void UnloadAllPreloadedResourceGroupsAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
