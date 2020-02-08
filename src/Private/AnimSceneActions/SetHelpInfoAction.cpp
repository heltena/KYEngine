#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SetHelpInfoAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string SetHelpInfoAction::XML_NODE = "set-help-info";

SetHelpInfoAction::SetHelpInfoAction()
{
}

SetHelpInfoAction::~SetHelpInfoAction()
{
}

SetHelpInfoAction* SetHelpInfoAction::readFromXml(TiXmlElement* element) {
	SetHelpInfoAction* action = new SetHelpInfoAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
    const std::string sceneRef = TiXmlHelper::readString(element, "scene-ref", true);
    const int level = TiXmlHelper::readInt(element, "level", true);
    const bool useMusicRef = TiXmlHelper::containsAttribute(element, "music-ref");
    std::string musicRef;
    if (useMusicRef)
        musicRef = TiXmlHelper::readString(element, "music-ref", true);
    const bool showIfFirst = TiXmlHelper::readBool(element, "show-if-first", true);
    
	action->setName(name);
    action->setSceneRef(sceneRef);
    action->setLevel(level);
    action->setUseMusicRef(useMusicRef);
    action->setMusicRef(musicRef);
    action->setShowIfFirst(showIfFirst);
    
	return action;
}

void SetHelpInfoAction::start(SceneTimelineInfo* info)
{
    Core::infoManager().setHelpInfo(m_sceneRef, m_level, m_useMusicRef, m_musicRef);
    if (m_showIfFirst && Core::infoManager().isHelpLocked(m_level))
        Core::sceneManager().pushAndSwitchToScene(m_sceneRef);
}

bool SetHelpInfoAction::isBlocking()
{
	return true;
}

bool SetHelpInfoAction::isFinished()
{
	return true;
}

void SetHelpInfoAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
