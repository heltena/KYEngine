#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Private/AnimSceneActions/ResumeHelpAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string ResumeHelpAction::XML_NODE = "resume-help";

ResumeHelpAction::ResumeHelpAction()
{
}

ResumeHelpAction::~ResumeHelpAction()
{
}

ResumeHelpAction* ResumeHelpAction::readFromXml(TiXmlElement* node)
{
	ResumeHelpAction* action = new ResumeHelpAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const bool unlockLevelHelp = TiXmlHelper::readBool(node, "unlock-level-help", false, true);
    
	action->setName(name);
	action->setUnlockLevelHelp(unlockLevelHelp);
    
	return action;
}

void ResumeHelpAction::start(SceneTimelineInfo* info)
{
    const HelpInfo& helpInfo = Core::infoManager().helpInfo();
    
    if (helpInfo.useMusicRef() && helpInfo.usingMusic())
        Core::soundManager().popMusic();
    
    if (m_unlockLevelHelp)
        Core::infoManager().unlockHelp(helpInfo.level());
    
    if (helpInfo.fromPause())
        Core::sceneManager().switchToScene("pause-scene", false);
    else
        Core::sceneManager().switchToPopedScene();
}

bool ResumeHelpAction::isBlocking()
{
	return true;
}

bool ResumeHelpAction::isFinished()
{
	return true;
}

void ResumeHelpAction::update(const double elapsedTime, SceneTimelineInfo* info)
{

}
