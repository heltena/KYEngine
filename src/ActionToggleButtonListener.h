#pragma once

#include <string>

class Entity;
class SceneTimelineInfo;

class ActionToggleButtonListener
{
public:
	virtual Entity* entity() = 0;
    virtual bool isActive(SceneTimelineInfo* info) const = 0;
    virtual void setOn(SceneTimelineInfo* info) = 0;
    virtual void setOff(SceneTimelineInfo* info) = 0;
};
