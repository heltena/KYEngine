#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class SetEntityInfoAction
	: public Action
{
public:
	SetEntityInfoAction();
	virtual ~SetEntityInfoAction();
	
public:
	static const std::string XML_NODE;
	static SetEntityInfoAction* readFromXml(TiXmlElement* node);
	
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
    void setUseAnimRef(bool useAnimRef) { m_useAnimRef = useAnimRef; }
    void setAnimRef(const std::string& animRef) { m_animRef = animRef; }
    void setUseX(bool useX) { m_useX = useX; }
    void setUseY(bool useY) { m_useY = useY; }
    void setUseZ(bool useZ) { m_useZ = useZ; }
    void setNewPos(const Vector4& newPos) { m_newPos = newPos; }

private:
	std::string m_name;
	std::string m_entityRef;
    bool m_useAnimRef;
    std::string m_animRef;
    bool m_useX;
    bool m_useY;
    bool m_useZ;
    Vector4 m_newPos;
};