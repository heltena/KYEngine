#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class BlinkAction
	: public Action
{
public:
	BlinkAction();
	virtual ~BlinkAction();

public:
	static const std::string XML_NODE;
	static BlinkAction* readFromXml(TiXmlElement* node);
	
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
    void setAmplitude(double amplitude) { m_amplitude = amplitude; }
    void setFrecuency(double frecuency) { m_frecuency = frecuency; }
    void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
	
private:
	std::string m_name;
    double m_amplitude;
    double m_frecuency;
    double m_elapsedTime;
	std::string m_entityRef;
	Entity* m_entity;
};