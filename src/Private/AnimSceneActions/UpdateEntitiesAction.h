#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>

#include <list>
#include <string>

class AnimSceneFactory;

class UpdateEntitiesAction
	: public Action
{
public:
	UpdateEntitiesAction();
	virtual ~UpdateEntitiesAction();

public:
	static const std::string XML_NODE;
	static UpdateEntitiesAction* readFromXml(TiXmlElement* node);
	
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
	
    void addAddEntityRef(const std::string& entityRef) { m_toAddEntityRef.push_back(entityRef); }
    void addRemoveEntityRef(const std::string& entityRef) { m_toRemoveEntityRef.push_back(entityRef); }
	
private:
	std::string m_name;
    std::list<std::string> m_toAddEntityRef;
    std::list<std::string> m_toRemoveEntityRef;
};