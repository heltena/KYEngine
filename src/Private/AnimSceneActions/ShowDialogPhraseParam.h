#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

class ShowDialogPhraseParam
{
public:
    ShowDialogPhraseParam();
    ShowDialogPhraseParam(const ShowDialogPhraseParam& other);
    virtual ~ShowDialogPhraseParam();
    
public:
	static const std::string XML_NODE;
	static ShowDialogPhraseParam* readFromXml(TiXmlElement* node);

public:
    const std::string& text() const { return m_text; }
    const Vector4& color() const { return m_color; }
    bool useTime() const { return m_useTime; }
    double time() const { return m_time; }

private:
    void setText(const std::string& text) { m_text = text; }
    void setColor(const Vector4& color) { m_color = color; }
    void setUseTime(bool useTime) { m_useTime = useTime; }
    void setTime(double time) { m_time = time; }

private:
    std::string m_text;
    Vector4 m_color;
    bool m_useTime;
    double m_time;
};