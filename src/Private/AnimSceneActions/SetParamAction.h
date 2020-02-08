#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class SetParamAction
	: public Action
{
public:
	SetParamAction();
	virtual ~SetParamAction();
	
public:
	static const std::string XML_NODE;
	static SetParamAction* readFromXml(TiXmlElement* node);
	
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
	
	const std::string& paramRef() const { return m_paramRef; }
	void setParamRef(const std::string& paramRef) { m_paramRef = paramRef; }
	const std::string& value() const { return m_value; }
	void setValue(const std::string& value) { m_value = value; }
	
private:
	std::string m_name;
	std::string m_paramRef;
	std::string m_value;
};