#pragma once

#include <KYEngine/Utility/EffectType.h>
#include <KYEngine/Utility/Vector4.h>

#include <map>
#include <string>

class InfoManager;

class PopupInfo
{
public:
    PopupInfo();
    PopupInfo(const PopupInfo& other);
    virtual ~PopupInfo();

public:
    double borderWidth() const { return m_borderWidth; }
    double borderHeight() const { return m_borderHeight; }
    const std::string& backgroundEntityRef() const { return m_backgroundEntityRef; }
    const std::string& fontRef() const { return m_fontRef; }
    const Vector4& pos() const { return m_pos; }
    double appearDuration() const { return m_appearDuration; }
    EffectType appearEffect() const { return m_appearEffect; }
    double appearAccelMagnitude() const { return m_appearAccelMagnitude; }
    double disappearDuration() const { return m_disappearDuration; }
    EffectType disappearEffect() const { return m_disappearEffect; }
    double disappearAccelMagnitude() const { return m_disappearAccelMagnitude; }
    const Vector4& color() const;
    bool useBackground() const { return m_useBackground; }
    
private:
    friend class InfoManager;
    void setBorderWidth(double borderWidth) { m_borderWidth = borderWidth; }
    void setBorderHeight(double borderHeight) { m_borderHeight = borderHeight; }
    void setBackgroundEntityRef(const std::string& backgroundEntityRef) { m_backgroundEntityRef = backgroundEntityRef; m_useBackground = true; }
    void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
    void setPos(const Vector4& pos) { m_pos = pos; }
    void setAppearDuration(double appearDuration) { m_appearDuration = appearDuration; }
    void setAppearEffect(EffectType appearEffect) { m_appearEffect = appearEffect; }
    void setAppearAccelMagnitude(double appearAccelMagnitude) { m_appearAccelMagnitude = appearAccelMagnitude; }
    void setDisappearDuration(double disappearDuration) { m_disappearDuration = disappearDuration; }
    void setDisappearEffect(EffectType disappearEffect) { m_disappearEffect = disappearEffect; }
    void setDisappearAccelMagnitude(double disappearAccelMagnitude) { m_disappearAccelMagnitude = disappearAccelMagnitude; }
    void setColor(const Vector4& color) { m_color = color; }
    
private:
    double m_borderWidth;
    double m_borderHeight;
    std::string m_backgroundEntityRef;
    std::string m_fontRef;
    Vector4 m_pos;
    double m_appearDuration;
    EffectType m_appearEffect;
    double m_appearAccelMagnitude;
    double m_disappearDuration;
    EffectType m_disappearEffect;
    double m_disappearAccelMagnitude;
    Vector4 m_color;
    bool m_useBackground;
};