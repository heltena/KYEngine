#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/PlaySoundAction.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Sound.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string PlaySoundAction::XML_NODE = "play-sound";

PlaySoundAction::PlaySoundAction()
{
}

PlaySoundAction::~PlaySoundAction()
{
}

PlaySoundAction* PlaySoundAction::readFromXml(TiXmlElement* node)
{
	PlaySoundAction* action = new PlaySoundAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string bufferRef = TiXmlHelper::readString(node, "buffer-ref", true);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", false, "");
	bool followEntity = entityRef != "";
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", NO_READ);
	double pitch = TiXmlHelper::readDouble(node, "pitch", false, 1.0);
	double gain = TiXmlHelper::readDouble(node, "gain", false, 1.0);
	bool loop = TiXmlHelper::readBool(node, "loop", false, false);
	bool autorelease = TiXmlHelper::readBool(node, "autorelease", false, true);
    const std::string executeIf = TiXmlHelper::readString(node, "execute-if", false, "true");
    
	action->setName(name);
	action->setBufferRef(bufferRef);
	action->setFollowEntity(followEntity);
	action->setEntityRef(entityRef);
	action->setInitialPos(initialPos);
	action->setPitch(pitch);
	action->setGain(gain);
	action->setLoop(loop);
	action->setAutorelease(autorelease);
	action->setExecuteIf(executeIf);
    
	return action;
}

void PlaySoundAction::start(SceneTimelineInfo* info)
{
    if (info->executeEL(m_executeIf) != "true")
        return;

	SoundBuffer* buffer = Core::resourceManager().soundBuffer(m_bufferRef);
	if (m_followEntity) {
		m_entity = Core::resourceManager().entity(m_entityRef);
		m_sound = Core::soundManager().playSound(m_soundName, buffer, m_entity, m_pitch, m_gain, m_loop, m_autorelease);
	} else
		m_sound = Core::soundManager().playSound(m_soundName, buffer, m_initialPos, m_pitch, m_gain, m_loop, m_autorelease);
	m_sound->play();
}

bool PlaySoundAction::isBlocking()
{
	return false;
}

bool PlaySoundAction::isFinished()
{
	return true;
}

void PlaySoundAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
