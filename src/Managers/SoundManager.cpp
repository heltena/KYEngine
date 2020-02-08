#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Music.h>
#include <KYEngine/Sound.h>
#include <KYEngine/SoundBuffer.h>
#include <KYEngine/Private/Resources/SoundImpl.h>
#include <KYEngine/Managers/SoundManager.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

const double SoundManager::SOUND_RATIO = 1;
const double SoundManager::MUSIC_TIMEOUT = 0.5; // timeout for delayed music

SoundManager::SoundManager()
	: m_volume(1)
    , m_listener(NULL)
	, m_music(NULL)
    , m_continuePlay(false)
{
    m_device = alcOpenDevice(NULL);
	
	if (!m_device)
		throw std::runtime_error("SoundManager cannot open device");
	
	m_context = alcCreateContext(m_device, NULL);
	alcMakeContextCurrent(m_context);
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	
	setListener(Vector4(480, 320, 0.1));
}

SoundManager::~SoundManager()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}

void SoundManager::setListener(Entity* listener)
{
	m_listener = listener;
	updateOpenALListener(m_listener->pos());
}

void SoundManager::setListener(const Vector4& listenerPos)
{
	m_listenerPos = listenerPos;
	m_listener = NULL;
	updateOpenALListener(m_listenerPos);
}

Sound* SoundManager::playSimpleSound(SoundBuffer *buffer, bool startPlay)
{
    int p = (int) Math::randomBetween(0, buffer->bufferCount());
    SoundImpl* result = new SoundImpl(buffer, p, m_listenerPos, 1, m_volume, false, true);
    m_nextUnnamedSoundId++;
    std::stringstream ss;
    ss << "#UNNAMED" << m_nextUnnamedSoundId;
    std::string soundName = ss.str();
#ifdef DEBUG
    std::map<std::string, SoundImpl*>::const_iterator found = m_sounds.find(soundName);
    if (found != m_sounds.end())
        throw std::runtime_error("SoundManager::playSound: sound is playing...");
#endif
    m_sounds[soundName] = result;
    if (startPlay)
        result->play();
    return result;
}

Sound* SoundManager::playSound(const std::string& soundName, SoundBuffer* buffer, Entity* follow, double pitch, double gain, bool loop, bool autorelease)
{
	int p = (int) Math::randomBetween(0, buffer->bufferCount());
    SoundImpl* result = new SoundImpl(buffer, p, follow, pitch, gain * m_volume, loop, autorelease);
#ifdef DEBUG
    std::map<std::string, SoundImpl*>::const_iterator found = m_sounds.find(soundName);
    if (found != m_sounds.end())
        throw std::runtime_error("SoundManager::playSound: sound is playing...");
#endif
	m_sounds[soundName] = result;
	return result;
}

Sound* SoundManager::playSound(const std::string& soundName, SoundBuffer* buffer, const Vector4& pos, double pitch, double gain, bool loop, bool autorelease)
{
	int p = (int) Math::randomBetween(0, buffer->bufferCount());
    SoundImpl* result = new SoundImpl(buffer, p, pos, pitch, gain * m_volume, loop, autorelease);
#ifdef DEBUG
    std::map<std::string, SoundImpl*>::const_iterator found = m_sounds.find(soundName);
    if (found != m_sounds.end())
        throw std::runtime_error("SoundManager::playSound: sound is playing...");
#endif
	m_sounds[soundName] = result;
	return result;
}

Sound* SoundManager::sound(const std::string& soundName)
{
    std::map<std::string, SoundImpl*>::const_iterator found = m_sounds.find(soundName);
#ifdef DEBUG
    if (found != m_sounds.end())
        throw std::runtime_error("SoundManager::playSound: sound is playing...");
#endif
	return found->second;
}

void SoundManager::removeSound(const std::string& soundName)
{
	std::map<std::string, SoundImpl*>::iterator found = m_sounds.find(soundName);
#ifdef DEBUG 
	if (found == m_sounds.end())
		throw std::runtime_error("SoundManager::removeSound cannot get sound: " + soundName);
#endif
	delete found->second;
	m_sounds.erase(found);
}

void SoundManager::removeAllSounds()
{
	for(std::map<std::string, SoundImpl*>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
		delete it->second;
	m_sounds.clear();
}

void SoundManager::update(const double elapsedTime)
{
	if (m_listener != NULL)
		updateOpenALListener(m_listener->pos());
	std::map<std::string, SoundImpl*>::iterator it = m_sounds.begin();
	while (it != m_sounds.end()) {
		bool release;
		it->second->update(elapsedTime, release);
		if (!release)
			it++;
		else {
			std::map<std::string, SoundImpl*>::iterator toKill = it++;
			delete toKill->second;
			m_sounds.erase(toKill);
		}
	}
    
    if (m_continuePlay) {
        m_musicTimeout -= elapsedTime;
        if (m_musicTimeout <= 0) {
            if (m_music != NULL)
                m_music->continuePlay(m_volume * SOUND_RATIO);
            m_continuePlay = false;
        }
    }
}
	
void SoundManager::updateOpenALListener(const Vector4& pos)
{
	ALfloat	listenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
	
	alListener3f(AL_POSITION, pos[0], pos[1], pos[2]);
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void SoundManager::changeMusic(Music* music)
{
    if (m_music == music)
		return;
	if (m_music != NULL)
		m_music->stop();
	m_music = music;
    m_continuePlay = false;
	if (m_music != NULL)
        m_music->play(m_volume * SOUND_RATIO);
}

void SoundManager::changeMusic(Music* music, double atTime)
{
    if (m_music != NULL)
        m_music->stop();
    m_music = music;
    m_continuePlay = false;
    if (m_music != NULL)
        m_music->play(m_volume * SOUND_RATIO, atTime);
}

void SoundManager::stopMusic()
{
	if (m_music != NULL)
		m_music->stop();
	m_music = NULL;    
    m_continuePlay = false;
}

void SoundManager::pushCurrentMusic()
{
    if (m_music == NULL)
        return;
    m_music->stop();
    m_musicStack.push_back(m_music);
}

void SoundManager::popMusic()
{
    if (m_music != NULL)
        m_music->stop();
    if (m_musicStack.size() == 0)
        m_music = NULL;
    else {
        m_music = m_musicStack.back();
        m_musicStack.pop_back();
        m_continuePlay = true;
        m_musicTimeout = MUSIC_TIMEOUT;
    }
}

void SoundManager::setVolume(float volume)
{
    m_volume = volume;
    if (m_music != NULL)
        m_music->setVolume(volume * SOUND_RATIO);
}

void SoundManager::mute()
{
    setVolume(0);
    for(std::map<std::string, SoundImpl*>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
        it->second->mute();
}

void SoundManager::unmute()
{
    setVolume(1);
    for(std::map<std::string, SoundImpl*>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
        it->second->unmute();
}
