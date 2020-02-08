#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class ScaleAction
	: public Action
{
public:
	ScaleAction();
	virtual ~ScaleAction();

public:
	static const std::string XML_NODE;
	static ScaleAction* readFromXml(TiXmlElement* node);
	
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
	void setTimes(int times) { m_times = times; }
	void setDuration(double duration) { m_duration = duration; }
    void setLoop(bool loop) { m_loop = loop; }
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setFromCurrentScale(bool fromCurrentScale) { m_fromCurrentScale = fromCurrentScale; }
	void setFrom(const Vector4& from) { m_from = from; }
	void setTo(const Vector4& to) { m_to = to; }
	void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
	
private:
	std::string m_name;
    int m_times;
	double m_duration;
    bool m_loop;
	double m_elapsedTime;
	std::string m_entityRef;
    bool m_fromCurrentScale;
	Vector4 m_from;
	Vector4 m_to;
	double m_accelMagnitude;
	Entity* m_entity;
};