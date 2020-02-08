#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class WaitForHudDisappearedAction
	: public Action
{
public:
	WaitForHudDisappearedAction();
	virtual ~WaitForHudDisappearedAction();
	
public:
	static const std::string XML_NODE;
	static WaitForHudDisappearedAction* readFromXml(TiXmlElement* node);
	
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
	
private:
	std::string m_name;
	bool m_isFinished;
};