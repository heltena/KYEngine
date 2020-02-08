#pragma once

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

class AnimSceneFactory;

class UseAtrezzoAction
    : public Action
{
public:
	UseAtrezzoAction();
	virtual ~UseAtrezzoAction();
	
public:
	static const std::string XML_NODE;
	static UseAtrezzoAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);
	
private:
	void setName(const std::string& name) { m_name = name; }
    void setAtrezzoRef(const std::string& atrezzoRef) { m_atrezzoRef = atrezzoRef; }
    void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
    void setCameraPos(const Vector4& cameraPos) { m_cameraPos = cameraPos; }
    
private:
	std::string m_name;
    std::string m_atrezzoRef;
    Vector4 m_initialPos;
    Vector4 m_cameraPos;
};