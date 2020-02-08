#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>

#include <list>
#include <string>

class AnimSceneFactory;

class UpdateGameCenterInfoAction
	: public Action
{
public:
	UpdateGameCenterInfoAction();
	virtual ~UpdateGameCenterInfoAction();

public:
	static const std::string XML_NODE;
	static UpdateGameCenterInfoAction* readFromXml(TiXmlElement* node);
	
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
};