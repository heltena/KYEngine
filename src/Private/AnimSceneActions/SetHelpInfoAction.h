#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class SetHelpInfoAction
	: public Action
{
public:
	SetHelpInfoAction();
	virtual ~SetHelpInfoAction();

public:
	static const std::string XML_NODE;
	static SetHelpInfoAction* readFromXml(TiXmlElement* node);

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
    void setLevel(int level) { m_level = level; }
    void setUseMusicRef(bool useMusicRef) { m_useMusicRef = useMusicRef; }
    void setMusicRef(const std::string& musicRef) { m_musicRef = musicRef; }
    void setShowIfFirst(bool showIfFirst) { m_showIfFirst = showIfFirst; }
    
private:
	std::string m_name;
    std::string m_sceneRef;
    int m_level;
    bool m_useMusicRef;
    std::string m_musicRef;
    bool m_showIfFirst;
};