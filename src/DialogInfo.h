#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <map>
#include <string>

class InfoManager;

class DialogInfo
{
public:
    DialogInfo();
    DialogInfo(const DialogInfo& other);
    virtual ~DialogInfo();

public:
    double borderWidth() const { return m_borderWidth; }
    double borderHeight() const { return m_borderHeight; }
    const std::string& backgroundEntityRef() const { return m_backgroundEntityRef; }
    const std::string& fontRef() const { return m_fontRef; }
    double z() const { return m_z; }
    double appearingCelerity() const { return m_appearingCelerity; }
    double disappearingCelerity() const { return m_disappearingCelerity; }
    const Vector4& color(const std::string& index) const;
    
private:
    friend class InfoManager;
    void setBorderWidth(double borderWidth) { m_borderWidth = borderWidth; }
    void setBorderHeight(double borderHeight) { m_borderHeight = borderHeight; }
    void setBackgroundEntityRef(const std::string& backgroundEntityRef) { m_backgroundEntityRef = backgroundEntityRef; }
    void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
    void setZ(double z) { m_z = z; }
    void setAppearingCelerity(double appearingCelerity) { m_appearingCelerity = appearingCelerity; }
    void setDisappearingCelerity(double disappearingCelerity) { m_disappearingCelerity = disappearingCelerity; }
    void addColor(const std::string& index, const Vector4& value);

private:
    double m_borderWidth;
    double m_borderHeight;
    std::string m_backgroundEntityRef;
    std::string m_fontRef;
    double m_z;
    double m_appearingCelerity;
    double m_disappearingCelerity;
    std::map<std::string, Vector4> m_color;
};