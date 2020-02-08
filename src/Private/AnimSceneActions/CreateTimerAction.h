#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class CreateTimerAction
	: public Action
{
public:
	CreateTimerAction();
	virtual ~CreateTimerAction();

public:
	static const std::string XML_NODE;
	static CreateTimerAction* readFromXml(TiXmlElement* node);

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
	
	const std::string& timerName() const { return m_timerName; }
	void setTimerName(const std::string& timerName) { m_timerName = timerName; }

private:
	std::string m_name;
	std::string m_timerName;
};