#pragma once

#include <KYEngine/Utility/Box.h>

#include <string>

class Entity;
class SceneTimelineInfo;

class ActionTouchingListener
{
public:
    virtual int touchId() = 0;
    virtual void touchOver(int touchId, SceneTimelineInfo* info) = 0;
    virtual void touchMovedOut(SceneTimelineInfo* info) = 0;
    virtual void touchMovedIn(SceneTimelineInfo* info) = 0;
    virtual void touchReleased(SceneTimelineInfo* info) = 0;
    virtual void touchCancelled(SceneTimelineInfo* info) = 0;
	virtual Entity* entity() = 0;
    virtual const Box screenBounds() const = 0;
    virtual void executeScript(SceneTimelineInfo* info) = 0;
};
