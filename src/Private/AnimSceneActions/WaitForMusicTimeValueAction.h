#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Music.h>

#include <string>

class AnimSceneFactory;

class WaitForMusicTimeValueAction
	: public Action
{
public:
	WaitForMusicTimeValueAction();
	virtual ~WaitForMusicTimeValueAction();
	
public:
	static const std::string XML_NODE;
	static WaitForMusicTimeValueAction* readFromXml(TiXmlElement* node);
	
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
    void setValue(double value) { m_value = value; }
    void setDelta(double delta) { m_delta = delta; }

private:
	std::string m_name;
    std::string m_musicRef;
    double m_value;
    double m_delta;
    double m_curDelta;
    bool m_finished;
    Music* m_music;
};