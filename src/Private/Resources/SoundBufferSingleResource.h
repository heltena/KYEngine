#pragma once

#include <tinyxml.h>

#include <KYEngine/Private/Resources/SoundBufferResource.h>

//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>

#include <string>

class SoundBufferSingleResource
    : public SoundBufferResource
{
public:
	SoundBufferSingleResource();
	virtual ~SoundBufferSingleResource();
    
public:
	static const std::string XML_NODE;
	static SoundBufferSingleResource* readFromXml(TiXmlElement* node);
	
// Resource implementation (partial in SoundBufferResource)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// SoundBuffer implementation
public:
	unsigned int bufferCount() const { return 1; }
	unsigned int bufferId(int index) const { return m_bufferId; }
    
private:
	void setFilename(const std::string& filename) { m_filename = filename; }
	void setFrequency(int frequency) { m_frequency = frequency; }
    
protected:
	bool m_loaded;
	unsigned int m_bufferId;
	std::string m_filename;
	int m_frequency;
};


