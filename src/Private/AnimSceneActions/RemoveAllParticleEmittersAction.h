#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class RemoveAllParticleEmittersAction
	: public Action
{
public:
	RemoveAllParticleEmittersAction();
	virtual ~RemoveAllParticleEmittersAction();
	
public:
	static const std::string XML_NODE;
	static RemoveAllParticleEmittersAction* readFromXml(TiXmlElement* node);
	
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

	
private:
	std::string m_name;
};