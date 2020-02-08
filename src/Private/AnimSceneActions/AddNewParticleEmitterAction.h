#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class AddNewParticleEmitterAction
	: public Action
{
private:
    static const double TOUCH_TIMEOUT;
    
public:
	AddNewParticleEmitterAction();
	virtual ~AddNewParticleEmitterAction();
	
public:
	static const std::string XML_NODE;
	static AddNewParticleEmitterAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return m_particleEmitterRef == name; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

public:
	void setName(const std::string& name) { m_name = name; }
	
    void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
    void setParticleEmitterRef(const std::string& particleEmitterRef) { m_particleEmitterRef = particleEmitterRef; }
    void setHasTimeout(bool hasTimeout) { m_hasTimeout = hasTimeout; }
    void setTimeout(double timeout) { m_timeout = timeout; }
    void setHasFollowEntityRef(bool hasFollowEntityRef) { m_hasFollowEntityRef = hasFollowEntityRef; }
    void setFollowEntityRef(const std::string& followEntityRef) { m_followEntityRef = followEntityRef; }
    void setFollowOffset(const Vector4& followOffset) { m_followOffset = followOffset; }
    void setSetIdAtParamName(const std::string& setIdAtParamName) { m_setIdAtParamName = setIdAtParamName; }
    void setExecuteIf(const std::string& executeIf) { m_executeIf = executeIf; }

private:
	std::string m_name;
    Vector4 m_initialPos;
	std::string m_particleEmitterRef;
    bool m_hasTimeout;
    double m_timeout;
    bool m_hasFollowEntityRef;
    std::string m_followEntityRef;
    Vector4 m_followOffset;
    std::string m_setIdAtParamName;
    std::string m_executeIf;
    bool m_isRunning;
    int m_particleEmitterId;
    Entity* m_followEntity;
};