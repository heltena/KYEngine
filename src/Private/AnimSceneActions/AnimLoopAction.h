#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>
#include <vector>

class AnimSceneFactory;

class AnimLoopAction
	: public Action
{
public:
	AnimLoopAction();
	virtual ~AnimLoopAction();

public:
	static const std::string XML_NODE;
	static AnimLoopAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return m_entityRef == name; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

public:
	void setName(const std::string& name) { m_name = name; }
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
	const std::string& entityRef() const { return m_entityRef; }
	
	void setLoop(const bool loop) { m_loop = loop; }
    
    void addAnimRef(const std::string& animRef) { m_animRefs.push_back(animRef); }
	void addDuration(const double& duration) {
		m_durations.push_back(duration); }
	
	
private:
	std::string m_name;
	double m_elapsedTime;
	std::string m_entityRef;
	bool m_loop;
	
	std::vector<std::string> m_animRefs;
	std::vector<double> m_durations;
	
	Entity* m_entity;
    int m_curSegment;
};