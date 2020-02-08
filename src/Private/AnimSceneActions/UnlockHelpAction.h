#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class UnlockHelpAction
	: public Action
{
public:
	UnlockHelpAction();
	virtual ~UnlockHelpAction();

public:
	static const std::string XML_NODE;
	static UnlockHelpAction* readFromXml(TiXmlElement* node);

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
	void setHelpLevel(int helpLevel) { m_helpLevel = helpLevel; }
    
private:
	std::string m_name;
    int m_helpLevel;
};