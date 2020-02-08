#pragma once

#include <KYEngine/Private/Huds/HudButton.h>
#include <KYEngine/Touch.h>
#include <KYEngine/TouchListener.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>

class HudJoystickButton
    : public HudButton
    , public TouchListener
{
public:
    HudJoystickButton();
    HudJoystickButton(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, double radius, Mesh* mesh, Mesh* overMesh, bool canMoveHorz, bool canMoveVert);
    virtual ~HudJoystickButton();

private:
    HudJoystickButton(const HudJoystickButton& other);

// HudButton implementation
public:
    virtual void appear(HudButtonListener* listener);
    virtual void disappear();
    Vector4 direction() const { return m_direction; }
    virtual void draw();
    
// TouchListener implementation
public:
    void touchesBegan(const std::map<int, Touch>& touches);
	void touchesMoved(const std::map<int, Touch>& touches);
	void touchesEnded(const std::map<int, Touch>& touches);
	void touchesCancelled(const std::map<int, Touch>& touches);

private:
    int m_touchId;
    bool m_canMoveHorz;
    bool m_canMoveVert;
    Vector4 m_direction;
    double m_radius;
    double m_sqrRadius; // radius * radius
};