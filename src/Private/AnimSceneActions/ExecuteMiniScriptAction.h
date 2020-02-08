#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class ExecuteMiniScriptAction
	: public Action
{
public:
	ExecuteMiniScriptAction();
	virtual ~ExecuteMiniScriptAction();
	
public:
	static const std::string XML_NODE;
	static ExecuteMiniScriptAction* readFromXml(TiXmlElement* node);
	
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
	void setScript(const std::string& script) { m_script = script; }
    void setExecuteIf(const std::string& executeIf) { m_executeIf = executeIf; }
    void setBlock(bool block) { m_block = block; }

private:
	std::string m_name;
	std::string m_script;
    std::string m_executeIf;
    bool m_block;
    bool m_finished;
};