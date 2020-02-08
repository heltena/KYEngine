#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/ChangeMusicAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string ChangeMusicAction::XML_NODE = "change-music";

ChangeMusicAction::ChangeMusicAction()
{
}

ChangeMusicAction::~ChangeMusicAction()
{
}

ChangeMusicAction* ChangeMusicAction::readFromXml(TiXmlElement* node)
{
	ChangeMusicAction* action = new ChangeMusicAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string musicRef = TiXmlHelper::readString(node, "music-ref", true);
    bool useAtTime = TiXmlHelper::containsAttribute(node, "at-time");
    const double atTime = TiXmlHelper::readDouble(node, "at-time", false, 0);
	
	action->setName(name);
	action->setMusicRef(musicRef);
    action->setUseAtTime(useAtTime);
	action->setAtTime(atTime);
    
	return action;
}

void ChangeMusicAction::start(SceneTimelineInfo* info)
{
	Music* music = Core::resourceManager().music(m_musicRef);
    if (m_useAtTime)
        Core::soundManager().changeMusic(music, m_atTime);
    else
        Core::soundManager().changeMusic(music);
}

bool ChangeMusicAction::isBlocking()
{
	return false;
}

bool ChangeMusicAction::isFinished()
{
	return true;
}

void ChangeMusicAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
