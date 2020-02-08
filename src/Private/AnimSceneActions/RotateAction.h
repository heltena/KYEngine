#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class RotateAction
	: public Action
{
public:
	RotateAction();
	virtual ~RotateAction();

public:
	static const std::string XML_NODE;
	static RotateAction* readFromXml(TiXmlElement* node);
	
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
    void setLoop(bool loop) { m_loop = loop; }
    void setCelerity(double celerity) { m_celerity = celerity; }
	void setDuration(double duration) { m_duration = duration; }
    void setFromCurrentAngle(bool fromCurrentAngle) { m_fromCurrentAngle = fromCurrentAngle; }
	void setFrom(double from) { m_from = from; }
	void setTo(double to) { m_to = to; }
	void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
	
private:
	std::string m_name;
	std::string m_entityRef;
    bool m_loop;
    double m_celerity;
	double m_duration;
	double m_elapsedTime;
    bool m_fromCurrentAngle;
	double m_from;
	double m_to;
	double m_accelMagnitude;
	Entity* m_entity;
};