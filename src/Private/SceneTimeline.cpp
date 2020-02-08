#include <KYEngine/Action.h>
#include <KYEngine/ActionBlockedListener.h>
#include <KYEngine/ActionToggleButtonListener.h>
#include <KYEngine/ActionTouchingListener.h>
#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>

#include <KYEngine/Private/AnimSceneActions/WaitForParamChangedAction.h>
#include <KYEngine/Private/Resources/MeshEntityResource.h>
#include <KYEngine/Private/SceneTimeline.h>

#include <KYEngine/RenderLayer.h>

#include <KYEngine/Utility/FunctionCallStatement.h>

#include <iostream>
#include <stdexcept>

SceneTimeline::SceneTimeline()
    : m_layerZOrder(1)
{
}

SceneTimeline::~SceneTimeline()
{
	for(std::list<Action*>::iterator it = m_actions.begin(); it != m_actions.end(); it++)
		delete *it;
}

const std::string& SceneTimeline::infoParam(const std::string& name)
{
    return m_params[name];
}

void SceneTimeline::infoScriptSetParam(const std::string& name, const std::string& value)
{
    setParam(name, value);
}

void SceneTimeline::hudButtonPressed(const Vector4& direction, int id)
{
    switch(id) {
    case 5:
        m_skipButtonPressed = true;
        break;
    }
}

void SceneTimeline::hudButtonReleased(const Vector4& direction, int id)
{
}

bool SceneTimeline::isActionFinished(const std::string& actionName)
{
	std::list<Action*>::iterator it = m_activeActions.begin();
	while (it != m_activeActions.end()) {
		Action* action = *it;
		if (action->name() == actionName)
			return action->isFinished();
		it++;
	}
	return true;
}

double SceneTimeline::sceneElapsedTime()
{
	return m_elapsedTime;
}

const std::string& SceneTimeline::param(const std::string& name)
{
#ifdef DEBUG 
	if (m_params.find(name) == m_params.end())
		throw std::runtime_error("param not found: " + name);
#endif
	return m_params[name];
}

void SceneTimeline::setParam(const std::string& name, const std::string& value)
{
	m_params[name] = value;
	std::list<ActionBlockedListener*>& actions = m_waitingParams[name];
	for(std::list<ActionBlockedListener*>::iterator it = actions.begin(); it != actions.end(); it++) {
		ActionBlockedListener* listener = *it;
		listener->actionUnblocked(this);
	}
	m_waitingParams.erase(name);
}

const std::string SceneTimeline::executeEL(const std::string &el)
{
    return Core::infoManager().executeEL(el, this);
}

void SceneTimeline::finishAction(const std::string& name)
{
	std::list<Action*>::iterator it = m_activeActions.begin();
	while (it != m_activeActions.end()) {
		Action* action = *it;
        if (action->name() == name) {
			std::list<Action*>::iterator toKill = it++;
            
            // Unblock other actions waiting "name"
            std::list<ActionBlockedListener*>& listeners = m_waitingActions[action->name()];
            for(std::list<ActionBlockedListener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
                ActionBlockedListener* listener = *it;
                listener->actionUnblocked(this);
            }
            m_waitingActions.erase(action->name());
        
            m_activeActions.erase(toKill);
        } else
            it++;
    }
}

void SceneTimeline::finishAllActiveActions()
{
	std::list<Action*>::iterator it = m_activeActions.begin();
	while (it != m_activeActions.end()) {
		Action* action = *it;
        std::list<Action*>::iterator toKill = it++;
            
        // Unblock other actions waiting "name"
        std::list<ActionBlockedListener*>& listeners = m_waitingActions[action->name()];
        for(std::list<ActionBlockedListener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
            ActionBlockedListener* listener = *it;
            listener->actionUnblocked(this);
        }
        m_waitingActions.erase(action->name());
            
        m_activeActions.erase(toKill);
    }
}

void SceneTimeline::waitForActionFinished(const std::string& name, ActionBlockedListener* listener)
{
	std::list<ActionBlockedListener*>& listeners = m_waitingActions[name];
	listeners.push_back(listener);
}

void SceneTimeline::waitForGlobalTouch(ActionBlockedListener* listener)
{
	m_waitingGlobalTouchs.push_back(listener);
}

void SceneTimeline::waitForParamChanged(const std::string& name, ActionBlockedListener* listener)
{
	std::list<ActionBlockedListener*>& listeners = m_waitingParams[name];
	listeners.push_back(listener);
}


void SceneTimeline::addTouchEvent(ActionTouchingListener* listener)
{
	m_touchingActions.insert(listener);
}

void SceneTimeline::removeTouchEvent(ActionTouchingListener* listener)
{
	m_touchingActions.erase(listener);
}

void SceneTimeline::removeAllTouchEvents()
{
	m_touchingActions.clear();
}

void SceneTimeline::addToggleButtonEvent(ActionToggleButtonListener* listener)
{
    m_toggleButtonActions.insert(listener);
}

void SceneTimeline::removeToggleButtonEvent(ActionToggleButtonListener* listener)
{
    m_toggleButtonActions.erase(listener);
}

void SceneTimeline::removeAllToggleButtonEvents()
{
    m_toggleButtonActions.clear();
}

void SceneTimeline::touchesBegan(const std::map<int, Touch>& touches)
{
    for(std::map<int, Touch>::const_iterator it = touches.begin(); it != touches.end(); it++) {
        if (! it->second.used()) {
            const Vector4& pos = it->second.pos();
            ActionTouchingListener* best = NULL;
            float bestZ = -1.0f;
            for (std::set<ActionTouchingListener*>::iterator it2 = m_touchingActions.begin(); it2 != m_touchingActions.end(); it2++) {
                ActionTouchingListener* listener = *it2;
                const Box& box = listener->screenBounds();
                if (box.contains(pos)) {
                    float curZ = listener->entity()->pos()[2];
                    if (curZ > bestZ) {
                        best = listener;
                        bestZ = curZ;
                    }
                }
            }
            if (best != NULL) {
                best->touchOver(it->first, this);
                it->second.used();
            }
        }
    }
}

void SceneTimeline::touchesMoved(const std::map<int, Touch>& touches)
{
    for (std::set<ActionTouchingListener*>::iterator it = m_touchingActions.begin(); it != m_touchingActions.end(); it++) {
        ActionTouchingListener* listener = *it;
        std::map<int, Touch>::const_iterator found = touches.find(listener->touchId());
        if (found != touches.end()) {
            const Vector4& pos = found->second.pos();
            const Box& box = listener->entity()->screenBounds();
            if (box.contains(pos))
                listener->touchMovedIn(this);
            else
                listener->touchMovedOut(this);
            found->second.used();
        }
    }
}

void SceneTimeline::touchesEnded(const std::map<int, Touch>& touches)
{
    for(std::map<int, Touch>::const_iterator it = touches.begin(); it != touches.end(); it++) {
        if (! it->second.used()) {
            bool touched = false;
            for (std::list<ActionBlockedListener*>::iterator it2 = m_waitingGlobalTouchs.begin();
                 it2 != m_waitingGlobalTouchs.end();
                 it2++) {
                ActionBlockedListener* action = *it2;
                action->actionUnblocked(this);
                touched = true;
            }
            m_waitingGlobalTouchs.clear();
            
            if (!touched) {
                for (std::set<ActionTouchingListener*>::iterator it2 = m_touchingActions.begin(); it2 != m_touchingActions.end(); it2++) {
                    ActionTouchingListener* listener = *it2;
                    if (listener->touchId() == it->first) {
                        listener->touchReleased(this);
                        listener->executeScript(this);
                        touched = true;
                    }
                }
            }
            
            if (!touched) {
                const Vector4& pos = it->second.pos();
                ActionToggleButtonListener* best = NULL;
                float bestZ = -1.0f;
                for (std::set<ActionToggleButtonListener*>::iterator it2 = m_toggleButtonActions.begin(); it2 != m_toggleButtonActions.end(); it2++) {
                    ActionToggleButtonListener* listener = *it2;
                    const Box& box = listener->entity()->screenBounds();
                    if (box.contains(pos)) {
                        float curZ = listener->entity()->pos()[2];
                        if (curZ > bestZ) {
                            best = listener;
                            bestZ = curZ;
                        }
                    }
                }
                
                if (best != NULL) {
                    bool isActive = best->isActive(this);
                    if (isActive)
                        best->setOff(this);
                    else
                        best->setOn(this);
                    touched = true;
                }
            }
            
            if (touched)
                it->second.used();
        }
    }
}

void SceneTimeline::touchesCancelled(const std::map<int, Touch>& touches)
{
    for (std::set<ActionTouchingListener*>::iterator it = m_touchingActions.begin(); it != m_touchingActions.end(); it++) {
        ActionTouchingListener* listener = *it;
        std::map<int, Touch>::const_iterator found = touches.find(listener->touchId());
        if (found != touches.end()) {
            listener->touchCancelled(this);
        }
    }
}

bool SceneTimeline::usePlayingHud() const
{
    return m_changeSceneIfHudTouched && ! Core::infoManager().isMotionLocked(m_motionName);
}

const std::string SceneTimeline::playingHudName() const
{
    return "skipHud";
}

PlayingHudListener* SceneTimeline::playingHudListener()
{
    return this;
}

void SceneTimeline::appear()
{
	m_elapsedTime = 0.0;
    m_skipButtonPressed = false;
	m_activeActions.clear();
	m_nextAction = m_actions.begin();
    
    if (m_useDarkLayer) {
        m_darkLayer = Core::renderManager().createLayer(m_layerRef + "#DARK", m_darkLayerZOrder);
        MeshEntityResource* entity = new MeshEntityResource();
        entity->setMeshRef(m_darkMeshRef);
        entity->load();
        
        m_darkEntity = entity;
        double width = Core::renderManager().width();
        double height = Core::renderManager().height();
        entity->setPos(Vector4(width / 2, height / 2, 0, 1));
        entity->setColor(Vector4::BLACK_TRANSPARENT);
        m_darkLayer->addEntity(entity, true);
    } else {
        m_darkLayer = NULL;
        m_darkEntity = NULL;
    }
    
	if (! m_createLayer)
		m_layer = Core::renderManager().layer(m_layerRef);
    else if (! Core::renderManager().containsLayer(m_layerRef))
        m_layer = Core::renderManager().createLayer(m_layerRef, m_layerZOrder);
    else if (! m_errorIfLayerExists)
        m_layer = Core::renderManager().layer(m_layerRef);
    else
        throw std::runtime_error("Cannot create layer again " + m_layerRef);
        
    Core::touchManager().addListener(this);
}

void SceneTimeline::disappear()
{
    Core::touchManager().removeListener(this);
}

void SceneTimeline::pushed()
{
    Core::touchManager().removeListener(this);
}

void SceneTimeline::poped()
{
    Core::touchManager().addListener(this);
}

void SceneTimeline::destroy()
{
    Core::touchManager().removeListener(this);
	if (m_destroyLayer || m_skipButtonPressed)
		Core::renderManager().removeLayer(m_layerRef);
    if (m_useDarkLayer)
        Core::renderManager().removeLayer(m_layerRef + "#DARK");
}

void SceneTimeline::abort()
{
    // TODO: stop all active actions
    Core::touchManager().removeListener(this);
    Core::renderManager().removeLayer(m_layerRef);
    if (m_useDarkLayer)
        Core::renderManager().removeLayer(m_layerRef + "#DARK");
}

void SceneTimeline::update(const double elapsedTime)
{
    if (m_skipButtonPressed) {
        Core::sceneManager().switchToScene(executeEL(m_sceneRef));
        return;
    }

	m_elapsedTime += elapsedTime;
	bool isBlocked = false;
	std::list<Action*>::iterator it = m_activeActions.begin();
	while (it != m_activeActions.end()) {
		Action* action = *it;
		action->update(elapsedTime, this);
		isBlocked = action->isBlocking();
		if (action->isFinished()) {
			std::list<Action*>::iterator toKill = it++;
			
			std::list<ActionBlockedListener*>& listeners = m_waitingActions[action->name()];
			for(std::list<ActionBlockedListener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
				ActionBlockedListener* listener = *it;
				listener->actionUnblocked(this);
			}
			m_waitingActions.erase(action->name());
			
            action->stop(this);
			m_activeActions.erase(toKill);
		} else
			it++;
	}
	
	while (! isBlocked && m_nextAction != m_actions.end()) {
		Action* action = *m_nextAction++;
		m_activeActions.push_back(action);
		action->start(this);
		isBlocked = action->isBlocking();
	}
}

void SceneTimeline::clearData()
{
    m_nextAction = m_actions.begin();
    while (m_nextAction != m_actions.end()) {
        delete *m_nextAction;
        m_nextAction++;
    }
    m_actions.clear();
    
    m_waitingActions.clear();
    m_waitingGlobalTouchs.clear();
    m_waitingParams.clear();
    m_toggleButtonActions.clear();
    m_touchingActions.clear();
}
