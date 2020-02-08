#pragma once

#include <tinyxml.h>

#include <KYEngine/Private/Resources/SoundBufferGroupInfo.h>
#include <KYEngine/Private/Resources/SoundBufferResource.h>

#include <vector>
#include <string>

class SoundBufferGroupResource
: public SoundBufferResource
{
public:
	static const std::string XML_NODE;
	static SoundBufferGroupResource* readFromXml(TiXmlElement* node);

public:
	SoundBufferGroupResource();
	virtual ~SoundBufferGroupResource();
	
// Resource implementation
public:
	const std::string& name() const { return m_name; }
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
    
// SoundSource implementation
public:
    unsigned int bufferCount() const { return m_info.size(); }
	unsigned int bufferId(int index) const { return m_info[index]->bufferId(); }

private:
    void setName(const std::string& name) { m_name = name; }
    void addSoundBufferGroupInfo(SoundBufferGroupInfo* info);

private:
    std::string m_name;
	bool m_loaded;
    std::vector<SoundBufferGroupInfo*> m_info;
};
