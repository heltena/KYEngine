#pragma once

#include <KYEngine/Sound.h>
#include <KYEngine/Utility/Vector4.h>

//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>

class Entity;
class SoundBuffer;
class SoundManager;

class SoundImpl
	: public Sound
{
private:
	friend class SoundManager;
	SoundImpl(SoundBuffer* buffer, int bufferIndex, Entity* follow, double pitch, double gain, bool loop, bool autorelease);
	SoundImpl(SoundBuffer* buffer, int bufferIndex, const Vector4& pos, double pitch, double gain, bool loop, bool autorelease);
	virtual ~SoundImpl();
	void init();
	void update(const double elapsedTime, bool& release);
	
public:
	void setPitch(double pitch);
	double pitch() const { return m_pitch; }
	void setGain(double gain);
	double gain() const { return m_gain; }
	void play();
	void stop();
	void pause();
    void mute();
    void unmute();

private:
    SoundBuffer* m_buffer;
    int m_bufferIndex;
	Entity* m_follow;
	Vector4 m_pos;
    bool m_playing;
	double m_pitch;
	double m_gain;
	bool m_loop;
	bool m_autorelease;
	bool m_stoppedByUser;
	unsigned int m_sourceId;
};
