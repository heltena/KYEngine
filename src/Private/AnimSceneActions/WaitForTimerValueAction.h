#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class WaitForTimerValueAction
	: public Action
{
public:
	WaitForTimerValueAction();
	virtual ~WaitForTimerValueAction();
	
public:
	static const std::string XML_NODE;
	static WaitForTimerValueAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);
	
public:
	void setName(const std::string& name) { m_name = name; }
	void setTimerRef(const std::string& timerRef) { m_timerRef = timerRef; }
    const std::string& timerRef() const { return m_timerRef; }
    void setValue(double value) { m_value = value; }
    double value() const { return m_value; }

private:
	std::string m_name;
    std::string m_timerRef;
    double m_value;
    int m_timerId;
};