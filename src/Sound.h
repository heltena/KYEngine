#pragma once

#include <string>

class Sound
{
protected:
    virtual ~Sound() { }
public:
    virtual void setPitch(double pitch) = 0;
	virtual double pitch() const = 0;
	virtual void setGain(double gain) = 0;
	virtual double gain() const = 0;
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual void pause() = 0;
    virtual void mute() = 0;
    virtual void unmute() = 0;
};