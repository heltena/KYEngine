#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Private/AnimSceneActions/UpdateGameCenterInfoAction.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

const std::string UpdateGameCenterInfoAction::XML_NODE = "update-game-center-info";

UpdateGameCenterInfoAction::UpdateGameCenterInfoAction()
{
}

UpdateGameCenterInfoAction::~UpdateGameCenterInfoAction()
{
}

UpdateGameCenterInfoAction* UpdateGameCenterInfoAction::readFromXml(TiXmlElement* node)
{
	UpdateGameCenterInfoAction* action = new UpdateGameCenterInfoAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");

	action->setName(name);
            
	return action;
}

void UpdateGameCenterInfoAction::start(SceneTimelineInfo* info)
{
    Core::infoManager().synchronizeGameCenterInfo();
}

bool UpdateGameCenterInfoAction::isBlocking()
{
	return false;
}

bool UpdateGameCenterInfoAction::isFinished()
{
	return true;
}

void UpdateGameCenterInfoAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
