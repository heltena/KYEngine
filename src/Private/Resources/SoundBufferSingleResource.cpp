#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Resources/SoundBufferSingleResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Utility/WaveReader.h>

#include <stdexcept>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

const std::string SoundBufferSingleResource::XML_NODE = "sound-buffer";

SoundBufferSingleResource* SoundBufferSingleResource::readFromXml(TiXmlElement* node)
{
    SoundBufferSingleResource* result = new SoundBufferSingleResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string filename = TiXmlHelper::readString(node, "filename", true);
    const int frequency = TiXmlHelper::readInt(node, "frequency", false, 44100);
	
	result->setName(name);
	result->setFilename(filename);
	result->setFrequency(frequency);
    return result;
}

SoundBufferSingleResource::SoundBufferSingleResource()
    : m_bufferId(0)
    , m_frequency(44100)
{
}

SoundBufferSingleResource::~SoundBufferSingleResource()
{
}

void SoundBufferSingleResource::preload()
{
}

void SoundBufferSingleResource::unloadFromPreloaded()
{
}

void SoundBufferSingleResource::load()
{
	alGenBuffers(1, &m_bufferId);
	
    WaveReader wr(filenamePath(m_filename));
	alBufferData(m_bufferId, AL_FORMAT_MONO16, wr.buffer(), wr.len(), m_frequency);
}

void SoundBufferSingleResource::unload()
{
	alDeleteBuffers(1, &m_bufferId);
}
