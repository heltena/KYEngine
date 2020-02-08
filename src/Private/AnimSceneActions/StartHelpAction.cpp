#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/StartHelpAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string StartHelpAction::XML_NODE = "start-help";

StartHelpAction::StartHelpAction()
{
}

StartHelpAction::~StartHelpAction()
{
}

StartHelpAction* StartHelpAction::readFromXml(TiXmlElement* node)
{
	StartHelpAction* action = new StartHelpAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void StartHelpAction::start(SceneTimelineInfo* info)
{
    const HelpInfo& helpInfo = Core::infoManager().helpInfo();
    bool helpUsingMusic = false;
    if (helpInfo.useMusicRef()) {
        Music* music = Core::resourceManager().music(helpInfo.musicRef());
        if (music != Core::soundManager().currentMusic()) {
            helpUsingMusic = true;
            Core::soundManager().pushCurrentMusic();
            Core::soundManager().changeMusic(music);
        }
    }
    Core::infoManager().setHelpUsingMusic(helpUsingMusic);
}

bool StartHelpAction::isBlocking()
{
	return false;
}

bool StartHelpAction::isFinished()
{
	return true;
}

void StartHelpAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
