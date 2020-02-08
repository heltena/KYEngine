#pragma once

#include <KYEngine/InfoScriptListener.h>

#include <KYEngine/PlayingHud.h>
#include <KYEngine/PlayingHudListener.h>

#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Touch.h>
#include <KYEngine/TouchListener.h>

#include <list>
#include <map>
#include <set>
#include <string>

class Action;
class AnimSceneImpl;
class RenderLayer;

class SceneTimeline
	: public InfoScriptListener
    , public PlayingHudListener
    , public SceneTimelineInfo
    , public TouchListener
{
private:
	friend class AnimSceneImpl;
	SceneTimeline();
	virtual ~SceneTimeline();

// InfoScriptListener implementation
public:
    virtual const std::string& infoParam(const std::string& name);
    virtual void infoScriptSetParam(const std::string& name, const std::string& value);

// PlayingHudListener implementation
public:
	void hudButtonPressed(const Vector4& direction, int id);
    void hudButtonReleased(const Vector4& direction, int id);
    
// SceneTimelineInfo implementation
public:
	RenderLayer* layer() { return m_layer; }
    Entity* darkEntity() { return m_darkEntity; }
	bool isActionFinished(const std::string& actionName);
	double sceneElapsedTime();

	const std::string& param(const std::string& name);
	void setParam(const std::string& name, const std::string& value);
	const std::string executeEL(const std::string& el);
    
    void finishAction(const std::string& name);
    void finishAllActiveActions();
    
	void waitForActionFinished(const std::string& name, ActionBlockedListener* listener);
	void waitForGlobalTouch(ActionBlockedListener* listener);
	void waitForParamChanged(const std::string& name, ActionBlockedListener* listener);
	
	void addTouchEvent(ActionTouchingListener* listener);
	void removeTouchEvent(ActionTouchingListener* listener);
	void removeAllTouchEvents();

    void addToggleButtonEvent(ActionToggleButtonListener* listener);
    void removeToggleButtonEvent(ActionToggleButtonListener* listener);
    void removeAllToggleButtonEvents();

// TouchListener implementation
public:
	void touchesBegan(const std::map<int, Touch>& touches);
	void touchesMoved(const std::map<int, Touch>& touches);
	void touchesEnded(const std::map<int, Touch>& touches);
	void touchesCancelled(const std::map<int, Touch>& touches);
    
public:
    void setMotionName(const std::string& motionName) { m_motionName = motionName; }
	void setLayerRef(const std::string& layerRef) { m_layerRef = layerRef; }
    void setLayerZOrder(int layerZOrder) { m_layerZOrder = layerZOrder; }
	void setCreateLayer(bool createLayer) { m_createLayer = createLayer; }
    void setErrorIfLayerExists(bool errorIfLayerExists) { m_errorIfLayerExists = errorIfLayerExists; }
	void setDestroyLayer(bool destroyLayer) { m_destroyLayer = destroyLayer; }
    void setChangeSceneIfHudTouched(bool changeSceneIfHudTouched) { m_changeSceneIfHudTouched = changeSceneIfHudTouched; }
    void setUseDarkLayer(bool useDarkLayer) { m_useDarkLayer = useDarkLayer; }
    void setDarkMeshRef(const std::string& darkMeshRef) { m_darkMeshRef = darkMeshRef; }
    void setDarkLayerZOrder(int darkLayerZOrder) { m_darkLayerZOrder = darkLayerZOrder; }
    void setSceneRef(const std::string& sceneRef) { m_sceneRef = sceneRef; }
	void addAction(Action* action) { m_actions.push_back(action); }
	
public:
    bool usePlayingHud() const;
    const std::string playingHudName() const;
    PlayingHudListener* playingHudListener();
	void appear();
	void disappear();
    void pushed();
    void poped();
	void destroy();
    void abort();
	void update(const double elapsedTime);

private:
	void clearData();

private:
    std::string m_motionName;
	std::string m_layerRef;
    int m_layerZOrder;
    int m_darkLayerZOrder;
	bool m_createLayer;
    bool m_errorIfLayerExists;
	bool m_destroyLayer;
    bool m_changeSceneIfHudTouched;
    bool m_skipButtonPressed;
    bool m_useDarkLayer;
    std::string m_darkMeshRef;
    std::string m_sceneRef;
	std::map<std::string, std::string> m_params;
	std::list<Action*> m_actions;
	std::list<Action*>::iterator m_nextAction;
	std::list<Action*> m_activeActions;
	std::map<std::string, std::list<ActionBlockedListener*> > m_waitingActions;
	std::list<ActionBlockedListener*> m_waitingGlobalTouchs;
	std::map<std::string, std::list<ActionBlockedListener*> > m_waitingParams;
    std::set<ActionToggleButtonListener*> m_toggleButtonActions;
	std::set<ActionTouchingListener*> m_touchingActions;
	double m_elapsedTime;
	
	RenderLayer* m_layer;
    RenderLayer* m_darkLayer;
    Entity* m_darkEntity;
};