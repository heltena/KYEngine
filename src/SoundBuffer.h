#pragma once

#include <string>

class SoundBuffer
{
public:
    virtual ~SoundBuffer() { }
    virtual const std::string& name() const = 0;
    virtual unsigned int bufferCount() const = 0;
	virtual unsigned int bufferId(int index) const = 0;
};