#pragma once

#include <KYEngine/Action.h>
#include <KYEngine/AddFaceViewParam.h>
#include <KYEngine/AddJoystickButtonParam.h>
#include <KYEngine/AddMapViewParam.h>
#include <KYEngine/AddProgressViewParam.h>
#include <KYEngine/AddPushButtonParam.h>

#include <tinyxml.h>

#include <string>

class AnimSceneFactory;

class UsePlayingHudAction
    : public Action
{
public:
	UsePlayingHudAction();
	virtual ~UsePlayingHudAction();
	
public:
	static const std::string XML_NODE;
	static UsePlayingHudAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);
	
private:
	void setName(const std::string& name) { m_name = name; }
    void setPlayingHudRef(const std::string& playingHudRef) { m_playingHudRef = playingHudRef; }

private:
	std::string m_name;
    std::string m_playingHudRef;
};