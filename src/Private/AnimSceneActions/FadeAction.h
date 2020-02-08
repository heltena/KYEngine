#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class FadeAction
	: public Action
{
public:
	FadeAction();
	virtual ~FadeAction();
	
public:
	static const std::string XML_NODE;
	static FadeAction* readFromXml(TiXmlElement* node);
	
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
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setFromCurrentAlpha(bool fromCurrentAlpha) { m_fromCurrentAlpha = fromCurrentAlpha; }
	void setFrom(double from) { m_from = from; }
	void setTo(const double to) { m_to = to; }
    void setOnlyAlpha(bool onlyAlpha) { m_onlyAlpha = onlyAlpha; }
    
private:
	std::string m_name;
	double m_duration;
	double m_elapsedTime;
	std::string m_entityRef;
    bool m_fromCurrentAlpha;
	double m_from;
	double m_to;
    bool m_onlyAlpha;
	Vector4 m_fromVector;
	Vector4 m_toVector;
	Entity* m_entity;
};