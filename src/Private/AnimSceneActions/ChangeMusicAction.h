#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class ChangeMusicAction
	: public Action
{
public:
	ChangeMusicAction();
	virtual ~ChangeMusicAction();
	
public:
	static const std::string XML_NODE;
	static ChangeMusicAction* readFromXml(TiXmlElement* node);
	
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
	
	void setMusicRef(const std::string& musicRef) { m_musicRef = musicRef; }
    void setUseAtTime(bool useAtTime) { m_useAtTime = useAtTime; }
    void setAtTime(double atTime) { m_atTime = atTime; }
    
private:
	std::string m_name;
	std::string m_musicRef;
    bool m_useAtTime;
    double m_atTime;
};