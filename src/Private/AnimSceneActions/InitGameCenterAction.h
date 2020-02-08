#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>

#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class InitGameCenterAction
	: public Action
{
public:
	InitGameCenterAction();
	virtual ~InitGameCenterAction();

public:
	static const std::string XML_NODE;
	static InitGameCenterAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

public:
	void setName(const std::string& name) { m_name = name; }
    void setHidePos(const Vector4& hidePos) { m_hidePos = hidePos; }
    void setShowPos(const Vector4& showPos) { m_showPos = showPos; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
	void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
	void setLineLength(double lineLength) { m_lineLength = lineLength; }
	void setLineSpacing(double lineSpacing) { m_lineSpacing = lineSpacing; }
	void setAlign(AlignType align) { m_align = align; }
    void setBorderColor(const Vector4& borderColor) { m_borderColor = borderColor; }
    void setPivot(const Vector4& pivot) { m_pivot = pivot; }
    void setAppearDuration(double appearDuration) { m_appearDuration = appearDuration; }
    void setShowingDuration(double showingDuration) { m_showingDuration = showingDuration; }
    void setDisappearDuration(double disappearDuration) { m_disappearDuration = disappearDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }

private:
	std::string m_name;
    Vector4 m_hidePos;
    Vector4 m_showPos;
    std::string m_meshRef;
	std::string m_fontRef;
	double m_lineLength;
	double m_lineSpacing;
	AlignType m_align;
	std::string m_defaultText;
    Vector4 m_pivot;
    Vector4 m_borderColor;
    double m_appearDuration;
    double m_showingDuration;
    double m_disappearDuration;
    double m_accelMagnitude;
};