#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>

#include <string>

class AnimSceneFactory;

class RemoveParticleEmitterAction
	: public Action
{
public:
	RemoveParticleEmitterAction();
	virtual ~RemoveParticleEmitterAction();
	
public:
	static const std::string XML_NODE;
	static RemoveParticleEmitterAction* readFromXml(TiXmlElement* node);
	
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
	
	void setParticleEmitterIdRef(const std::string& particleEmitterIdRef) { m_particleEmitterIdRef = particleEmitterIdRef; }
	
private:
	std::string m_name;
	std::string m_particleEmitterIdRef;
};