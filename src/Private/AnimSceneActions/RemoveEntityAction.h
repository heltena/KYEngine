#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class RemoveEntityAction
	: public Action
{
public:
	RemoveEntityAction();
	virtual ~RemoveEntityAction();
	
public:
	static const std::string XML_NODE;
	static RemoveEntityAction* readFromXml(TiXmlElement* node);
	
	// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return m_entityRef == name; }
	void update(const double elapsedTime, SceneTimelineInfo* info);
	
public:
	void setName(const std::string& name) { m_name = name; }
	
	const std::string& entityRef() const { return m_entityRef; }
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
	
private:
	std::string m_name;
	std::string m_entityRef;
};