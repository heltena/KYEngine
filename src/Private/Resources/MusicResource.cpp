#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Resources/MusicResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string MusicResource::XML_NODE = "music";

MusicResource* MusicResource::readFromXml(TiXmlElement* node)
{
    MusicResource* result = new MusicResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string filename = TiXmlHelper::readString(node, "filename", true);
    const bool initialLoop = TiXmlHelper::readBool(node, "initial-loop", false, true);
	
	result->setName(name);
	result->setFilename(filename);
    result->setInitialLoop(initialLoop);
    
    return result;
}

MusicResource::MusicResource()
	: m_loaded(false)
    , m_musicData(NULL)
{
}

MusicResource::~MusicResource()
{
}

void MusicResource::preload()
{
}

void MusicResource::unloadFromPreloaded()
{
}

void MusicResource::load()
{
    if (m_musicData != NULL)
        throw std::runtime_error("MusicResource::load cannot load again");
    m_musicData = NULL;
}

void MusicResource::unload()
{
    stop();
}


void MusicResource::play(float volume, double atTime)
{
    if (m_musicData != NULL)
        stop();
	m_musicData = musicLoad(m_filename, volume, m_initialLoop);
	musicPlay(m_musicData, volume, atTime);
}

void MusicResource::continuePlay(float volume)
{
    play(volume, m_lastTime);
}

void MusicResource::stop()
{
    if (m_musicData == NULL)
        return;
    m_lastTime = currentTime();
    musicStop(m_musicData);
    musicUnload(m_musicData);
    m_musicData = NULL;
}

bool MusicResource::isPlaying() const
{
    if (m_musicData == NULL)
        return false;
    return musicIsPlaying(m_musicData);
}

void MusicResource::setVolume(float volume)
{
    if (m_musicData == NULL)
        return;
    musicSetVolume(m_musicData, volume);
}

void MusicResource::setLoop(bool loop)
{
    if (m_musicData == NULL)
        return;
    musicSetLoop(m_musicData, loop);
}

bool MusicResource::loop() const
{
    if (m_musicData == NULL)
        return false;
    return musicLoop(m_musicData);
}

double MusicResource::currentTime()
{
    return musicCurrentTime(m_musicData);
}

double MusicResource::duration()
{
    return musicDuration(m_musicData);
}
