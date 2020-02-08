#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/ActionBlockedListener.h>

#include <string>

class AnimSceneFactory;

class WaitForTouchAction
	: public Action
	, public ActionBlockedListener
{
public:
	WaitForTouchAction();
	virtual ~WaitForTouchAction();
	
public:
	static const std::string XML_NODE;
	static WaitForTouchAction* readFromXml(TiXmlElement* node);
	
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
	
private:
	std::string m_name;
	bool m_isFinished;
};