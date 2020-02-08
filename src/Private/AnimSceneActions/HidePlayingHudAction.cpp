#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/HidePlayingHudAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string HidePlayingHudAction::XML_NODE = "hide-playing-hud";

HidePlayingHudAction::HidePlayingHudAction()
{
}

HidePlayingHudAction::~HidePlayingHudAction()
{
}

HidePlayingHudAction* HidePlayingHudAction::readFromXml(TiXmlElement* node)
{
	HidePlayingHudAction* action = new HidePlayingHudAction();
    
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void HidePlayingHudAction::start(SceneTimelineInfo* info)
{
    Core::hudManager().playingHud().disappear();
}

bool HidePlayingHudAction::isBlocking()
{
	return false;
}

bool HidePlayingHudAction::isFinished()
{
	return Core::hudManager().playingHud().isDisappeared();
}

void HidePlayingHudAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
