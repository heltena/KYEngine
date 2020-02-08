#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>
#include <vector>

class AnimSceneFactory;

class BezierMoveAction
	: public Action
{
public:
	BezierMoveAction();
	virtual ~BezierMoveAction();

public:
	static const std::string XML_NODE;
	static BezierMoveAction* readFromXml(TiXmlElement* node);
	
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
    
    void addRefPoint(const Vector4& refPoint) { m_refPoints.push_back(refPoint); }
	
private:
	std::string m_name;
	double m_duration;
	double m_elapsedTime;
	std::string m_entityRef;
    std::vector<Vector4> m_refPoints;
    std::vector<double> m_combs;
	Entity* m_entity;
};