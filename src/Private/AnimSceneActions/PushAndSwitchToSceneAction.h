#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class PushAndSwitchToSceneAction
	: public Action
{
public:
	PushAndSwitchToSceneAction();
	virtual ~PushAndSwitchToSceneAction();
	
public:
	static const std::string XML_NODE;
	static PushAndSwitchToSceneAction* readFromXml(TiXmlElement* node);
	
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
	void setSceneRef(const std::string& sceneRef) { m_sceneRef = sceneRef; }
    void setExecuteIf(const std::string& executeIf) { m_executeIf = executeIf; }
    
private:
	std::string m_name;
	std::string m_sceneRef;
    std::string m_executeIf;
};