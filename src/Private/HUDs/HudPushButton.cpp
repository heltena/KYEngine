#include <KYEngine/Core.h>
#include <KYEngine/Private/Huds/HudPushButton.h>

#include <iostream>

HudPushButton::HudPushButton()
{
}

HudPushButton::HudPushButton(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, double radius, Mesh* mesh, Mesh* overMesh)
    : HudButton(id, name, appearedPos, disappearedPos, animDuration, accelMagnitude, mesh, overMesh)
    , m_radius(radius)
    , m_sqrRadius(radius * radius)
    , m_pressed(false)
    , m_released(false)
{
}

HudPushButton::HudPushButton(const HudPushButton& other)
    : HudButton(other)
    , m_radius(other.m_radius)
    , m_sqrRadius(other.m_sqrRadius)
    , m_pressed(other.m_pressed)
    , m_released(other.m_released)
{
}

HudPushButton::~HudPushButton()
{
}

void HudPushButton::appear(HudButtonListener* listener)
{
    HudButton::appear(listener);
    m_pressed = false;
    m_released = false;
    Core::touchManager().addListener(this);
}

void HudPushButton::disappear()
{
    HudButton::disappear();
    Core::touchManager().removeListener(this);
}

void HudPushButton::touchesBegan(const std::map<int, Touch>& touches)
{
    std::map<int, Touch>::const_iterator it = touches.begin();
    while (!isSelected() && it != touches.end()) {
        const Touch& t = it->second;
        if (! t.used()) {
            const Vector4 diff = t.pos() - m_appearedPos;
            if (diff.sqrlen() < m_sqrRadius) {
                t.setUsed();
                m_touchId = it->first;
                select();
            }
        }
        it++;
    }
}

void HudPushButton::touchesMoved(const std::map<int, Touch>& touches)
{
    if (! isSelected())
        return;
    
    std::map<int, Touch>::const_iterator found = touches.find(m_touchId);
    if (found == touches.end() || found->second.used())
        return;
    
    const Touch& t = found->second;
    const Vector4 diff = t.pos() - m_appearedPos;
    double sl = diff.sqrlen();
    if (sl >= m_sqrRadius)
        release();
    found->second.setUsed();
}

void HudPushButton::touchesEnded(const std::map<int, Touch>& touches)
{
    if (! isSelected())
        return;
    
    std::map<int, Touch>::const_iterator found = touches.find(m_touchId);
    if (found == touches.end() || found->second.used())
        return;
    
    release();
    found->second.setUsed();
}

void HudPushButton::touchesCancelled(const std::map<int, Touch>& touches)
{
    if (! isSelected())
        return;
    
    std::map<int, Touch>::const_iterator found = touches.find(m_touchId);
    if (found == touches.end() || found->second.used())
        return;
    
    release();
    found->second.setUsed();
}
