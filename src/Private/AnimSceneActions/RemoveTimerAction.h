#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class RemoveTimerAction
	: public Action
{
public:
	RemoveTimerAction();
	virtual ~RemoveTimerAction();

public:
	static const std::string XML_NODE;
	static RemoveTimerAction* readFromXml(TiXmlElement* node);

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
	
	const std::string& timerRef() const { return m_timerRef; }
	void setTimerRef(const std::string& timerRef) { m_timerRef = timerRef; }

private:
	std::string m_name;
	std::string m_timerRef;
};