#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Resources/SoundBufferGroupResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string SoundBufferGroupResource::XML_NODE = "sound-buffer-group";

SoundBufferGroupResource* SoundBufferGroupResource::readFromXml(TiXmlElement* node)
{
    SoundBufferGroupResource* result = new SoundBufferGroupResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);

    result->setName(name);
    
    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
		if (value == SoundBufferGroupInfo::XML_NODE) {
            SoundBufferGroupInfo* newItem = SoundBufferGroupInfo::readFromXml(curr);
			result->addSoundBufferGroupInfo(newItem);
		} else
			throw std::runtime_error("SoundBufferGroupResource(" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}

    return result;
}

SoundBufferGroupResource::SoundBufferGroupResource()
{
}

SoundBufferGroupResource::~SoundBufferGroupResource()
{
    for(std::vector<SoundBufferGroupInfo*>::iterator it = m_info.begin(); it != m_info.end(); it++) {
        SoundBufferGroupInfo* info = *it;
        delete info;
    }
}

void SoundBufferGroupResource::preload()
{
}

void SoundBufferGroupResource::unloadFromPreloaded()
{
}

void SoundBufferGroupResource::load()
{
    for(std::vector<SoundBufferGroupInfo*>::iterator it = m_info.begin(); it != m_info.end(); it++) {
        SoundBufferGroupInfo* info = *it;
        info->load();
    }
}

void SoundBufferGroupResource::unload()
{
    for(std::vector<SoundBufferGroupInfo*>::iterator it = m_info.begin(); it != m_info.end(); it++) {
        SoundBufferGroupInfo* info = *it;
        info->unload();
    }
}

void SoundBufferGroupResource::addSoundBufferGroupInfo(SoundBufferGroupInfo* info)
{
    m_info.push_back(info);
}