#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class ChangeColorAction
	: public Action
{
public:
	ChangeColorAction();
	virtual ~ChangeColorAction();

public:
	static const std::string XML_NODE;
	static ChangeColorAction* readFromXml(TiXmlElement* node);
	
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
	
	void setDuration(double duration) { m_duration = duration; }
	double duration() const { return m_duration; }
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
	const std::string& entityRef() const { return m_entityRef; }
	
    void setFromCurrentColor(bool fromCurrentColor) { m_fromCurrentColor = fromCurrentColor; }
    bool fromCurrentColor() const { return m_fromCurrentColor; }
    
	void setFrom(const Vector4& from) { m_from = from; }
	Vector4& from() { return m_from; }
	
	void setTo(const Vector4& to) { m_to = to; }
	Vector4& to() { return m_to; }

	void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
	double accelMagnitude() const { return m_accelMagnitude; }
	
private:
	std::string m_name;
	double m_duration;
	double m_elapsedTime;
	std::string m_entityRef;
    bool m_fromCurrentColor;
	Vector4 m_from;
	Vector4 m_to;
	double m_accelMagnitude;
	Entity* m_entity;
};