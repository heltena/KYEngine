#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class WalkAction
	: public Action
{
public:
	WalkAction();
	virtual ~WalkAction();

public:
	static const std::string XML_NODE;
	static WalkAction* readFromXml(TiXmlElement* node);
	
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
    void setSteps(double steps) { m_steps = steps; }
    void setAmplitude(double amplitude) { m_amplitude = amplitude; }
    void setDuration(double duration) { m_duration = duration; }
    void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setFromCurrentPos(bool fromCurrentPos) { m_fromCurrentPos = fromCurrentPos; }
	void setFrom(const Vector4& from) { m_from = from; }
	void setTo(const Vector4& to) { m_to = to; }
	
private:
	std::string m_name;
    double m_steps;
    double m_amplitude;
    double m_duration;
    double m_elapsedTime;
	std::string m_entityRef;
    bool m_fromCurrentPos;
	Vector4 m_from;
	Vector4 m_to;
	Entity* m_entity;
};