#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class AddEntityAction
	: public Action
{
public:
	AddEntityAction();
	virtual ~AddEntityAction();

public:
	static const std::string XML_NODE;
	static AddEntityAction* readFromXml(TiXmlElement* node);

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
	void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
	void setInitialColor(const Vector4& initialColor) { m_initialColor = initialColor; }
    void setInitialAngle(const double initialAngle) { m_initialAngle = initialAngle; }
    void setInitialScale(const Vector4& initialScale) { m_initialScale = initialScale; }
    void setUseAnimRef(bool useAnimRef) { m_useAnimRef = useAnimRef; }
    void setAnimRef(const std::string& animRef) { m_animRef = animRef; }
    void setUseUseBlending(bool useUseBlending) { m_useUseBlending = useUseBlending; }
    void setUseBlending(bool useBlending) { m_useBlending = useBlending; }
    
private:
	std::string m_name;
	std::string m_entityRef;
	Vector4 m_initialPos;
	Vector4 m_initialColor;
    double m_initialAngle;
    Vector4 m_initialScale;
    bool m_useAnimRef;
    std::string m_animRef;
    bool m_useUseBlending;
    bool m_useBlending;
};