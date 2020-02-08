#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Resources/SoundBufferGroupInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Utility/WaveReader.h>

#include <stdexcept>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

const std::string SoundBufferGroupInfo::XML_NODE = "sound";

SoundBufferGroupInfo* SoundBufferGroupInfo::readFromXml(TiXmlElement* node)
{
    SoundBufferGroupInfo* result = new SoundBufferGroupInfo();
	const std::string filename = TiXmlHelper::readString(node, "filename", true);
    const int frequency = TiXmlHelper::readInt(node, "frequency", false, 44100);
	
	result->setFilename(filename);
	result->setFrequency(frequency);
    return result;
}

SoundBufferGroupInfo::SoundBufferGroupInfo()
//    : m_buffer(NULL)
{
}

SoundBufferGroupInfo::~SoundBufferGroupInfo()
{
}

void SoundBufferGroupInfo::load()
{
    alGenBuffers(1, &m_bufferId);
    
//    if (m_buffer != NULL)
//        throw std::runtime_error("SoundBufferGroupInfo: buffer not delivered");
    WaveReader wr(filenamePath(m_filename));
    alBufferData(m_bufferId, AL_FORMAT_MONO16, wr.buffer(), wr.len(), m_frequency);
}

void SoundBufferGroupInfo::unload()
{
	//free(m_buffer);
    //m_buffer = NULL;
	alDeleteBuffers(1, &m_bufferId);
}
