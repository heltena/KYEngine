#pragma once

#include <string>

class ActionBlockedListener;
class ActionTouchingListener;
class ActionToggleButtonListener;
class Entity;
class RenderLayer;

class SceneTimelineInfo
{
public:
	virtual RenderLayer* layer() = 0;
    virtual Entity* darkEntity() = 0;
	virtual bool isActionFinished(const std::string& actionName) = 0;
	virtual double sceneElapsedTime() = 0;
	
	virtual const std::string& param(const std::string& name) = 0;
	virtual void setParam(const std::string& name, const std::string& value) = 0;
	virtual const std::string executeEL(const std::string& el) = 0;
    
    virtual void finishAction(const std::string& name) = 0;
    virtual void finishAllActiveActions() = 0;
    
	virtual void waitForActionFinished(const std::string& name, ActionBlockedListener* listener) = 0;
	virtual void waitForGlobalTouch(ActionBlockedListener* listener) = 0;
	virtual void waitForParamChanged(const std::string& name, ActionBlockedListener* listener) = 0;
	
	virtual void addTouchEvent(ActionTouchingListener* listener) = 0;
	virtual void removeTouchEvent(ActionTouchingListener* listener) = 0;
	virtual void removeAllTouchEvents() = 0;

    virtual void addToggleButtonEvent(ActionToggleButtonListener* listener) = 0;
    virtual void removeToggleButtonEvent(ActionToggleButtonListener* listener) = 0;
    virtual void removeAllToggleButtonEvents() = 0;
};
