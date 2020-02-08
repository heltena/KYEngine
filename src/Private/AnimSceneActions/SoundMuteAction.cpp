#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SoundMuteAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string SoundMuteAction::XML_NODE = "sound-mute";

SoundMuteAction::SoundMuteAction()
{
}

SoundMuteAction::~SoundMuteAction()
{
}

SoundMuteAction* SoundMuteAction::readFromXml(TiXmlElement* node)
{
	SoundMuteAction* action = new SoundMuteAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void SoundMuteAction::start(SceneTimelineInfo* info)
{
    Core::soundManager().mute();
}

bool SoundMuteAction::isBlocking()
{
	return false;
}

bool SoundMuteAction::isFinished()
{
	return true;
}

void SoundMuteAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
