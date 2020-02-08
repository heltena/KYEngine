#pragma once

#include <KYEngine/RawData.h>
#include <KYEngine/Private/Resources/Resource.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class RawDataResource
	: public RawData
    , public Resource
{
public:
	RawDataResource();
	virtual ~RawDataResource();
	
// Resource partial implementation
public:
	const std::string& name() const { return m_name; }
    virtual void preload() = 0;
    virtual void unloadFromPreloaded() = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
	void* userData() = 0;

// RawData partial implementation
public:
    virtual void* data() = 0;

protected:
	void setName(const std::string& name) { m_name = name; }
	
protected:
	std::string m_name;
};
