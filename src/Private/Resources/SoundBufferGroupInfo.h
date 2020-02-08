#pragma once

#include <string>
#include <tinyxml.h>

//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>

class SoundBufferGroupInfo
{
public:
    SoundBufferGroupInfo();
    virtual ~SoundBufferGroupInfo();

public:
	static const std::string XML_NODE;
	static SoundBufferGroupInfo* readFromXml(TiXmlElement* node);

public:
    void load();
    void unload();
    
public:
    const std::string& filename() const { return m_filename; }
    unsigned int bufferId() const { return m_bufferId; }
    int frequency() const { return m_frequency; }

private:
    void setFilename(const std::string& filename) { m_filename = filename; }
    void setFrequency(int frequency) { m_frequency = frequency; }

private:
    bool m_loaded;
	//void* m_buffer;
	std::string m_filename;
    unsigned int m_bufferId;
    int m_frequency;
};