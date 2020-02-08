#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimSceneFactory;

class SetTextAction
	: public Action
{
public:
	SetTextAction();
	virtual ~SetTextAction();
	
public:
	static const std::string XML_NODE;
	static SetTextAction* readFromXml(TiXmlElement* node);
	
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
	void setText(const std::string& text) { m_text = text; }
    void setUseLineLength(bool useLineLength) { m_useLineLength = useLineLength; }
	void setLineLength(double lineLength) { m_lineLength = lineLength; }
    void setUseLineSpacing(bool useLineSpacing) { m_useLineSpacing = useLineSpacing; }
    void setLineSpacing(double lineSpacing) { m_lineSpacing = lineSpacing; }
    void setUseAlignment(bool useAlignment) { m_useAlignment = useAlignment; }
    void setAlign(AlignType align) { m_align = align; }

private:
	std::string m_name;
	std::string m_entityRef;
	std::string m_text;
    bool m_useLineLength;
    double m_lineLength;
    bool m_useLineSpacing;
    double m_lineSpacing;
    bool m_useAlignment;
    AlignType m_align;
};