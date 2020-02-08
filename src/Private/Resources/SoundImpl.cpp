#include <KYEngine/Entity.h>
#include <KYEngine/SoundBuffer.h>
#include <KYEngine/Private/Resources/SoundImpl.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

SoundImpl::SoundImpl(SoundBuffer* buffer, int bufferIndex, Entity* follow, double pitch, double gain, bool loop, bool autorelease)
	: m_buffer(buffer)
    , m_bufferIndex(bufferIndex)
	, m_follow(follow)
    , m_playing(false)
	, m_pitch(pitch)
	, m_gain(gain)
	, m_loop(loop)
	, m_autorelease(autorelease)
{
	init();
}

SoundImpl::SoundImpl(SoundBuffer* buffer, int bufferIndex, const Vector4& pos, double pitch, double gain, bool loop, bool autorelease)
	: m_buffer(buffer)
    , m_bufferIndex(bufferIndex)
	, m_follow(NULL)
    , m_playing(false)
	, m_pos(pos)
	, m_pitch(pitch)
	, m_gain(gain)
	, m_loop(loop)
	, m_autorelease(autorelease)
	, m_stoppedByUser(false)
{
	init();
}

SoundImpl::~SoundImpl()
{
	alDeleteSources(1, &m_sourceId);
}

void SoundImpl::init()
{
	ALenum err = alGetError(); // clear the error code
	
	unsigned int bufferId = m_buffer->bufferId(m_bufferIndex);
	alGenSources(1, &m_sourceId);
	
	alSourcei(m_sourceId, AL_BUFFER, 0);
	alSourcei(m_sourceId, AL_BUFFER, bufferId);

	Vector4 pos;
	if (m_follow)
		pos = m_follow->pos();
	else
		pos = m_pos;

	alSource3f(m_sourceId, AL_POSITION, pos[0], pos[1], pos[2]);
	alSource3f(m_sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	
	alSourcef(m_sourceId, AL_PITCH, m_pitch);
	alSourcef(m_sourceId, AL_GAIN, m_gain);

	alSourcef(m_sourceId, AL_REFERENCE_DISTANCE, 1000.f);
	alSourcef(m_sourceId, AL_MAX_DISTANCE,       10000.f);
	alSourcef(m_sourceId, AL_ROLLOFF_FACTOR,     100.1f);
	
	
	alSourcei(m_sourceId, AL_LOOPING, m_loop ? AL_TRUE : AL_FALSE);
	
	err = alGetError();
	if (err != 0)
		throw std::runtime_error("SoundImpl cannot play this sound");
        
    m_playing = false;
}

void SoundImpl::update(const double elapsedTime, bool& release)
{
	release = false;
	ALint state;
    alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING && ! m_stoppedByUser && m_autorelease)
		release = true;
	if (! m_follow)
		return;
	Vector4 pos = m_follow->pos();
	alSource3f(m_sourceId, AL_POSITION, pos[0], pos[1], pos[2]);
}

void SoundImpl::setPitch(double pitch)
{
	m_pitch = pitch;
	alSourcef(m_sourceId, AL_PITCH, m_pitch);
}

void SoundImpl::setGain(double gain)
{
	m_gain = gain;
	alSourcef(m_sourceId, AL_GAIN, m_gain);
}

void SoundImpl::play()
{
    if (m_playing)
        return;
    m_playing = true;
	m_stoppedByUser = false;
	alSourcePlay(m_sourceId);
}

void SoundImpl::stop()
{
    if (!m_playing)
        return;
    m_playing = false;
	m_stoppedByUser = true;
	alSourceStop(m_sourceId);
}

void SoundImpl::pause()
{
    m_playing = false;
	alSourcePause(m_sourceId);
}

void SoundImpl::mute()
{
    alSourcef(m_sourceId, AL_GAIN, 0);
}

void SoundImpl::unmute()
{
    alSourcef(m_sourceId, AL_GAIN, m_gain);
}
