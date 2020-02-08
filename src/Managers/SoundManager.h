#pragma once

#include <map>
#include <string>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

class Core;
class Entity;
class Vector4;
class Sound;
class SoundImpl;
class Music;

class SoundManager
{
private:
    static const double SOUND_RATIO;
    static const double MUSIC_TIMEOUT;
    
private:
	friend class Core;
	SoundManager();
	virtual ~SoundManager();

public:
	void setListener(Entity* listener);
	void setListener(const Vector4& listenerPos);
	
    Sound* playSimpleSound(SoundBuffer* buffer, bool startPlay = true);
	Sound* playSound(const std::string& soundName, SoundBuffer* buffer, Entity* follow, double pitch, double gain, bool loop, bool autorelease);
	Sound* playSound(const std::string& soundName, SoundBuffer* buffer, const Vector4& pos, double pitch, double gain, bool loop, bool autorelease);
	Sound* sound(const std::string& soundName);
	
	void removeSound(const std::string& soundName);
	void removeAllSounds();
	void update(const double elapsedTime);
	
    void changeMusic(Music* music);
	void changeMusic(Music* music, double atTime);
	void stopMusic();
    
    Music* currentMusic() { return m_music; }
    void pushCurrentMusic();
    void popMusic();
    
    void setVolume(float volume);
    float volume() const { return m_volume; }
    
    void mute();
    void unmute();
    
private:
	void updateOpenALListener(const Vector4& pos);
	
private:
    float m_volume;
	ALCcontext* m_context;
	ALCdevice* m_device;
	
	Vector4 m_listenerPos;
	Entity* m_listener;

    int m_nextUnnamedSoundId;
	std::map<std::string, SoundImpl*> m_sounds;
	Music* m_music;
    std::list<Music*> m_musicStack;
    
    // Info for delayed play
    bool m_continuePlay;
    double m_musicTimeout;
};
