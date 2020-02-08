#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/LoadGlobalResourcesAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string LoadGlobalResourcesAction::XML_NODE = "load-global-resources";

LoadGlobalResourcesAction::LoadGlobalResourcesAction()
{
}

LoadGlobalResourcesAction::~LoadGlobalResourcesAction()
{
}

LoadGlobalResourcesAction* LoadGlobalResourcesAction::readFromXml(TiXmlElement* node)
{
	LoadGlobalResourcesAction* action = new LoadGlobalResourcesAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    
	action->setName(name);

	return action;
}

void LoadGlobalResourcesAction::start(SceneTimelineInfo* info)
{
    Core::resourceManager().loadGlobalResources();
}

bool LoadGlobalResourcesAction::isBlocking()
{
	return false;
}

bool LoadGlobalResourcesAction::isFinished()
{
	return true;
}

void LoadGlobalResourcesAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
