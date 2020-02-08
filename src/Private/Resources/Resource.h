#pragma once

#include <string>

class Resource
{
public:
    virtual ~Resource() { }
	virtual const std::string& name() const = 0;
    virtual void preload() = 0;
    virtual void unloadFromPreloaded() = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
    virtual void* userData() = 0;
};
