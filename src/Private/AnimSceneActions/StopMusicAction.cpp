#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/StopMusicAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string StopMusicAction::XML_NODE = "stop-music";

StopMusicAction::StopMusicAction()
{
}

StopMusicAction::~StopMusicAction()
{
}

StopMusicAction* StopMusicAction::readFromXml(TiXmlElement* node)
{
	StopMusicAction* action = new StopMusicAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void StopMusicAction::start(SceneTimelineInfo* info)
{
    Core::soundManager().stopMusic();
}

bool StopMusicAction::isBlocking()
{
	return false;
}

bool StopMusicAction::isFinished()
{
	return true;
}

void StopMusicAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
