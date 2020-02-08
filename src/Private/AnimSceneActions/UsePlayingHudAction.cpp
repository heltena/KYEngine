#include <KYEngine/AddFaceViewParam.h>
#include <KYEngine/AddMapViewParam.h>
#include <KYEngine/AddProgressViewParam.h>
#include <KYEngine/AddPushButtonParam.h>
#include <KYEngine/AddJoystickButtonParam.h>
#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/UsePlayingHudAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string UsePlayingHudAction::XML_NODE = "use-playing-hud";

UsePlayingHudAction::UsePlayingHudAction()
{
}

UsePlayingHudAction::~UsePlayingHudAction()
{
}

UsePlayingHudAction* UsePlayingHudAction::readFromXml(TiXmlElement* node)
{
	UsePlayingHudAction* action = new UsePlayingHudAction();
    
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string playingHudRef = TiXmlHelper::readString(node, "playing-hud-ref", true);
    
	action->setName(name);
    action->setPlayingHudRef(playingHudRef);
    
    return action;
}

void UsePlayingHudAction::start(SceneTimelineInfo* info)
{
    Core::hudManager().usePlayingHud(m_playingHudRef);
    PlayingHud& playingHud = Core::hudManager().playingHud();
    playingHud.appear(NULL);
}

bool UsePlayingHudAction::isBlocking()
{
	return false;
}

bool UsePlayingHudAction::isFinished()
{
	return Core::hudManager().playingHud().isAppeared();
}

void UsePlayingHudAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
