#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class EarnAchievementAction
	: public Action
{
public:
	EarnAchievementAction();
	virtual ~EarnAchievementAction();

public:
	static const std::string XML_NODE;
	static EarnAchievementAction* readFromXml(TiXmlElement* node);

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
	void setAchievementID(const std::string& achievementID) { m_achievementID = achievementID; }
    void setPercentage(const std::string& percentage) { m_percentage = percentage; }
private:
	std::string m_name;
	std::string m_achievementID;
    std::string m_percentage;
};