#pragma once

#include <string>

class Music
{
public:
    virtual ~Music() { }
    virtual const std::string& name() const = 0;
	virtual void play(float volume, double atTime = 0) = 0;
    virtual void continuePlay(float volume) = 0;
	virtual void stop() = 0;
    virtual bool isPlaying() const = 0;
    virtual void setVolume(float volume) = 0;
    virtual void setLoop(bool loop) = 0;
    virtual bool loop() const = 0;
    virtual double currentTime() = 0;
    virtual double duration() = 0;
};
