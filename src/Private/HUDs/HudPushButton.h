#pragma once

#include <KYEngine/Private/Huds/HudButton.h>
#include <KYEngine/TouchListener.h>

class HudPushButton
    : public HudButton
    , public TouchListener
{
public:
    HudPushButton();
    HudPushButton(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, double radius, Mesh* mesh, Mesh* overMesh);
    virtual ~HudPushButton();
    
private:
    HudPushButton(const HudPushButton& other);

// HudButton implementation
public:
    virtual void appear(HudButtonListener* listener);
    virtual void disappear();
    
// TouchListener implementation
public:
    void touchesBegan(const std::map<int, Touch>& touches);
    void touchesMoved(const std::map<int, Touch>& touches);
    void touchesEnded(const std::map<int, Touch>& touches);
    void touchesCancelled(const std::map<int, Touch>& touches);

private:
    int m_touchId;
    double m_radius;
    double m_sqrRadius; // radius * radius
    bool m_pressed;
    bool m_released;
};