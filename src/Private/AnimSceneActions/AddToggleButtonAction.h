#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/ActionToggleButtonListener.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class AddToggleButtonAction
	: public Action
	, public ActionToggleButtonListener
{
public:
	AddToggleButtonAction();
	virtual ~AddToggleButtonAction();
	
public:
	static const std::string XML_NODE;
	static AddToggleButtonAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return m_entityRef == name; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

// ActionToggleButtonListener implementation
public:
	Entity* entity() { return m_entity; }
    bool isActive(SceneTimelineInfo* info) const;
    void setOn(SceneTimelineInfo* info);
    void setOff(SceneTimelineInfo* info);
	
public:
	void setName(const std::string& name) { m_name = name; }
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setOffAnimRef(const std::string& offAnimRef) { m_offAnimRef = offAnimRef; }
    void setOnAnimRef(const std::string& onAnimRef) { m_onAnimRef = onAnimRef; }
    void setInitValue(const std::string& initValue) { m_initValue = initValue; }
    void setToOffScript(const std::string& toOffScript) { m_toOffScript = toOffScript; }
    void setToOnScript(const std::string& toOnScript) { m_toOnScript = toOnScript; }
	
private:
	std::string m_name;
	std::string m_entityRef;
    std::string m_offAnimRef;
    std::string m_onAnimRef;
    std::string m_initValue;
    std::string m_toOffScript;
    std::string m_toOnScript;
	Entity* m_entity;
    bool m_isActive;
};