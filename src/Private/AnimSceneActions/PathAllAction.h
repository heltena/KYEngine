#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>
#include <vector>

class AnimSceneFactory;

class PathAllAction
	: public Action
{
public:
	PathAllAction();
	virtual ~PathAllAction();

public:
	static const std::string XML_NODE;
	static PathAllAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info);
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
    
    void addRefPoint(const Vector4& refPoint) { m_refPositionPoints.push_back(refPoint); }
    void addRefScalePoint(const Vector4& refScalePoint) { m_refScalePoints.push_back(refScalePoint); }
	
private:
	std::string m_name;
	double m_duration;
	double m_elapsedTime;
	std::string m_entityRef;
    std::vector<Vector4> m_refPositionPoints;
    std::vector<Vector4> m_refScalePoints;
    std::vector<double> m_durations;
	Entity* m_entity;
    int m_curSegment;
};