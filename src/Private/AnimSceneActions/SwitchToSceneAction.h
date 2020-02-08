#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class SwitchToSceneAction
	: public Action
{
public:
	SwitchToSceneAction();
	virtual ~SwitchToSceneAction();
	
public:
	static const std::string XML_NODE;
	static SwitchToSceneAction* readFromXml(TiXmlElement* node);
	
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
    void setDestroyStack(bool destroyStack) { m_destroyStack = destroyStack; }
    
private:
	std::string m_name;
	std::string m_sceneRef;
    bool m_destroyStack;
};