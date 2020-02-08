#pragma once

#include <tinyxml.h>

#include <KYEngine/SoundBuffer.h>
#include <KYEngine/Private/Resources/Resource.h>

//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>

#include <string>

class SoundBufferResource
	: public Resource
	, public SoundBuffer
{
public:
	SoundBufferResource();
	virtual ~SoundBufferResource();
    
// Resource implementation
public:
	const std::string& name() const { return m_name; }
    
// SoundBuffer implementation
public:

protected:
	void setName(const std::string& name) { m_name = name; }
    
private:
    std::string m_name;
};


