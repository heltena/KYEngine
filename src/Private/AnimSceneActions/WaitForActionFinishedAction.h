#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/ActionBlockedListener.h>

class AnimSceneFactory;

class WaitForActionFinishedAction
	: public Action
	, public ActionBlockedListener
{
public:
	WaitForActionFinishedAction();
	virtual ~WaitForActionFinishedAction();
	
public:
	static const std::string XML_NODE;
	static WaitForActionFinishedAction* readFromXml(TiXmlElement* node);
	
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
	void setActionRef(const std::string& actionRef) { m_actionRef = actionRef; }
	
private:
	std::string m_name;
	std::string m_actionRef;
	bool m_isFinished;
};