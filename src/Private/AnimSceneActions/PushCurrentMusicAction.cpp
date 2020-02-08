#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/PushCurrentMusicAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string PushCurrentMusicAction::XML_NODE = "push-current-music";

PushCurrentMusicAction::PushCurrentMusicAction()
{
}

PushCurrentMusicAction::~PushCurrentMusicAction()
{
}

PushCurrentMusicAction* PushCurrentMusicAction::readFromXml(TiXmlElement* node)
{
	PushCurrentMusicAction* action = new PushCurrentMusicAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void PushCurrentMusicAction::start(SceneTimelineInfo* info)
{
	Core::soundManager().pushCurrentMusic();
}

bool PushCurrentMusicAction::isBlocking()
{
	return false;
}

bool PushCurrentMusicAction::isFinished()
{
	return true;
}

void PushCurrentMusicAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
