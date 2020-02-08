#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SoundUnmuteAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string SoundUnmuteAction::XML_NODE = "sound-unmute";

SoundUnmuteAction::SoundUnmuteAction()
{
}

SoundUnmuteAction::~SoundUnmuteAction()
{
}

SoundUnmuteAction* SoundUnmuteAction::readFromXml(TiXmlElement* node)
{
	SoundUnmuteAction* action = new SoundUnmuteAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void SoundUnmuteAction::start(SceneTimelineInfo* info)
{
    Core::soundManager().unmute();
}

bool SoundUnmuteAction::isBlocking()
{
	return false;
}

bool SoundUnmuteAction::isFinished()
{
	return true;
}

void SoundUnmuteAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
