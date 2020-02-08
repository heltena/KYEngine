#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/ActionTouchingListener.h>
#include <KYEngine/SoundBuffer.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class AddTouchEventAction
	: public Action
	, public ActionTouchingListener
{
private:
    static const double TOUCH_TIMEOUT;
    
public:
	AddTouchEventAction();
	virtual ~AddTouchEventAction();
	
public:
	static const std::string XML_NODE;
	static AddTouchEventAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return m_entityRef == name; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

// ActionTouchingListener implementation (partial implementation, more after next 'public')
public:
    int touchId() { return m_touchId; }
    void touchOver(int touchId, SceneTimelineInfo* info);
    void touchMovedOut(SceneTimelineInfo* info);
    void touchMovedIn(SceneTimelineInfo* info);
    void touchReleased(SceneTimelineInfo* info);
    void touchCancelled(SceneTimelineInfo* info);
	Entity* entity() { return m_entity; }
    const Box screenBounds() const;
    void executeScript(SceneTimelineInfo* info);
	
public:
	void setName(const std::string& name) { m_name = name; }
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setAnimReleased(const std::string& animReleased) { m_animReleased = animReleased; }
    void setAnimOver(const std::string& animOver) { m_animOver = animOver; }
    void setSoundRef(const std::string& soundRef) { m_soundRef = soundRef; }
	void setScript(const std::string& script) { m_script = script; }
	void setBoundsAddSize(const Vector4& boundsAddSize) { m_boundsAddSize = boundsAddSize; }

    void setUseTelemetry(bool useTelemetry) { m_useTelemetry = useTelemetry; }
    void setTelemetryCategory(const std::string& telemetryCategory) { m_telemetryCategory = telemetryCategory; }
    void setTelemetryAction(const std::string& telemetryAction) { m_telemetryAction = telemetryAction; }
    void setTelemetryLabel(const std::string& telemetryLabel) { m_telemetryLabel = telemetryLabel; }
    void setTelemetryValue(int telemetryValue) { m_telemetryValue = telemetryValue; }

private:
	std::string m_name;
	std::string m_entityRef;
    std::string m_animReleased;
    std::string m_animOver;
    std::string m_soundRef;
	std::string m_script;
    Vector4 m_boundsAddSize;
    
    bool m_useTelemetry;
    std::string m_telemetryCategory;
    std::string m_telemetryAction;
    std::string m_telemetryLabel;
    int m_telemetryValue;
    
	Entity* m_entity;
    SoundBuffer* m_sound;
    int m_touchId;
    std::string m_curAnimReleased;
    std::string m_curAnimOver;
    double m_touchTimeout;
};