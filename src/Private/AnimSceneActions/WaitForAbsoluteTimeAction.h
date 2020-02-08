#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class WaitForAbsoluteTimeAction
	: public Action
{
public:
	WaitForAbsoluteTimeAction();
	virtual ~WaitForAbsoluteTimeAction();
	
public:
	static const std::string XML_NODE;
	static WaitForAbsoluteTimeAction* readFromXml(TiXmlElement* node);
	
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
	void setAbsoluteTime(double absoluteTime) { m_absoluteTime = absoluteTime; }
	double absoluteTime() const { return m_absoluteTime; }

private:
	std::string m_name;
	double m_absoluteTime;
    bool m_finished;
};