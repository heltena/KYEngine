#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/KYLocale.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class SetLocaleAction
	: public Action
{
public:
	SetLocaleAction();
	virtual ~SetLocaleAction();
	
public:
	static const std::string XML_NODE;
	static SetLocaleAction* readFromXml(TiXmlElement* node);
	
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
	
	const std::string& locale() const { return m_locale; }
	void setLocale(const std::string& locale) { m_locale = locale; }
	
private:
	std::string m_name;
	std::string m_locale;
};