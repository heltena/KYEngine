#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class AddTextEntityAction
	: public Action
{
public:
	AddTextEntityAction();
	virtual ~AddTextEntityAction();
	
public:
	static const std::string XML_NODE;
	static AddTextEntityAction* readFromXml(TiXmlElement* node);
	
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
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
    void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
	void setInitialColor(const Vector4& initialColor) { m_initialColor = initialColor; }
    void setInitialAngle(const double initialAngle) { m_initialAngle = initialAngle; }
    void setInitialScale(const Vector4& initialScale) { m_initialScale = initialScale; }
    void setUsePivot(bool usePivot) { m_usePivot = usePivot; }
    void setPivot(const Vector4& pivot) { m_pivot = pivot; }
	void setText(const std::string& text) { m_text = text; }
    void setUseLineLength(bool useLineLength) { m_useLineLength = useLineLength; }
	void setLineLength(double lineLength) { m_lineLength = lineLength; }
    void setUseLineSpacing(bool useLineSpacing) { m_useLineSpacing = useLineSpacing; }
    void setLineSpacing(double lineSpacing) { m_lineSpacing = lineSpacing; }
    void setUseAlignment(bool useAlignment) { m_useAlignment = useAlignment; }
    void setAlign(AlignType align) { m_align = align; }
    void setUseBlending(bool useBlending) { m_useBlending = useBlending; }

private:
	std::string m_name;
	std::string m_entityRef;
	Vector4 m_initialPos;
	Vector4 m_initialColor;
    double m_initialAngle;
    Vector4 m_initialScale;
	std::string m_text;
    bool m_usePivot;
    Vector4 m_pivot;
    bool m_useLineLength;
    double m_lineLength;
    bool m_useLineSpacing;
    double m_lineSpacing;
    bool m_useAlignment;
    AlignType m_align;
    bool m_useBlending;
};