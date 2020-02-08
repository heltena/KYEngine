#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/ActionBlockedListener.h>

class AnimSceneFactory;

class WaitForParamChangedAction
	: public Action
	, public ActionBlockedListener
{
public:
	WaitForParamChangedAction();
	virtual ~WaitForParamChangedAction();
	
public:
	static const std::string XML_NODE;
	static WaitForParamChangedAction* readFromXml(TiXmlElement* node);
	
	// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

// ActionBlockedListener implementation
public:
	void actionUnblocked(SceneTimelineInfo* info) { m_isFinished = true; }

public:
	void setName(const std::string& name) { m_name = name; }
	void setParamRef(const std::string& paramRef) { m_paramRef = paramRef; }
	void paramChanged() { m_isFinished = true; }
	
private:
	std::string m_name;
	std::string m_paramRef;
	bool m_isFinished;
};