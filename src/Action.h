#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <string>

class SceneTimelineInfo;

class Action
{
public:
    virtual ~Action() { }
	virtual const std::string& name() const = 0;
	virtual void start(SceneTimelineInfo* info) = 0;
    virtual void stop(SceneTimelineInfo* info) = 0;
	virtual bool isBlocking() = 0;
	virtual bool isFinished() = 0;
    virtual bool isUsingEntity(const std::string& name) = 0;
	virtual void update(const double elapsedTime, SceneTimelineInfo* info) = 0;
};