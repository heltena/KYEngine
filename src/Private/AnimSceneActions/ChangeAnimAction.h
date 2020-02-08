#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class ChangeAnimAction
	: public Action
{
public:
	ChangeAnimAction();
	virtual ~ChangeAnimAction();
	
public:
	static const std::string XML_NODE;
	static ChangeAnimAction* readFromXml(TiXmlElement* node);
	
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
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
	const std::string& entityRef() const { return m_entityRef; }

	void setAnimRef(const std::string& animRef) { m_animRef = animRef; }
	const std::string& animRef() const { return m_animRef; }

private:
	std::string m_name;
	std::string m_entityRef;
	std::string m_animRef;
};