#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class MoveAction
	: public Action
{
public:
	MoveAction();
	virtual ~MoveAction();

public:
	static const std::string XML_NODE;
	static MoveAction* readFromXml(TiXmlElement* node);
	
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
    void setUseCelerity(bool useCelerity) { m_useCelerity = useCelerity; }
	void setDuration(double duration) { m_duration = duration; }
    void setCelerity(double celerity) { m_celerity = celerity; }
    void setLoop(bool loop) { m_loop = loop; }
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setFromCurrentPos(bool fromCurrentPos) { m_fromCurrentPos = fromCurrentPos; }
	void setFrom(const Vector4& from) { m_from = from; }
	void setTo(const Vector4& to) { m_to = to; }
	void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
	
private:
	std::string m_name;
    int m_times;
    bool m_useCelerity;
	double m_duration;
    double m_celerity;
    bool m_loop;
	double m_elapsedTime;
	std::string m_entityRef;
    bool m_fromCurrentPos;
	Vector4 m_from;
	Vector4 m_to;
	double m_accelMagnitude;
	Entity* m_entity;
};