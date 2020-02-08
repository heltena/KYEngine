#pragma once

#include <KYEngine/AddTextLabelParam.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Private/Huds/HudTextLabel.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

class AddTextLabelParamImpl
    : public AddTextLabelParam
{
public:
    AddTextLabelParamImpl();
    AddTextLabelParamImpl(const AddTextLabelParamImpl& other);
    virtual ~AddTextLabelParamImpl();
    
public:
	static const std::string XML_NODE;
	static AddTextLabelParamImpl* readFromXml(TiXmlElement* node);

public:
    const std::string& fontRef() const { return m_fontRef; }
    const std::string& defaultText() const { return m_defaultText; }
    const Vector4& appearedPos() const { return m_appearedPos; }
    const Vector4& disappearedPos() const { return m_disappearedPos; }
    double animDuration() const { return m_animDuration; }
    double accelMagnitude() const { return m_accelMagnitude; }
    const Vector4& color() const { return m_color; }
    const Vector4& borderColor() const { return m_borderColor; }
    double lineLength() const { return m_lineLength; }
    double lineSpacing() const { return m_lineSpacing; }
    AlignType align() const { return m_align; }
    
// AddTextLabelParam implementation
public:
    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    HudTextLabel* generateTextLabel() const;
    
private:
    void setId(int id) { m_id = id; }
    void setName(const std::string& name) { m_name = name; }
    void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
    void setDefaultText(const std::string& defaultText) { m_defaultText = defaultText; }
    void setAppearedPos(const Vector4& appearedPos) { m_appearedPos = appearedPos; }
    void setDisappearedPos(const Vector4& disappearedPos) { m_disappearedPos = disappearedPos; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
    void setColor(const Vector4& color) { m_color = color; }
    void setBorderColor(const Vector4& borderColor) { m_borderColor = borderColor; }
    void setLineLength(double lineLength) { m_lineLength = lineLength; }
    void setLineSpacing(double lineSpacing) { m_lineSpacing = lineSpacing; }
    void setAlign(AlignType align) { m_align = align; }
    
private:
    int m_id;
    std::string m_name;
    std::string m_fontRef;
    std::string m_defaultText;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    double m_animDuration;
    double m_accelMagnitude;
    Vector4 m_color;
    Vector4 m_borderColor;
    double m_lineLength;
    double m_lineSpacing;
    AlignType m_align;
};