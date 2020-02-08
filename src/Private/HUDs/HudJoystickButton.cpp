#include <KYEngine/Core.h>
#include <KYEngine/Private/Huds/HudJoystickButton.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

HudJoystickButton::HudJoystickButton()
{
}

HudJoystickButton::HudJoystickButton(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, double radius, Mesh* mesh, Mesh* overMesh, bool canMoveHorz, bool canMoveVert)
    : HudButton(id, name, appearedPos, disappearedPos, animDuration, accelMagnitude, mesh, overMesh)
    , m_radius(radius)
    , m_sqrRadius(radius * radius)
    , m_canMoveHorz(canMoveHorz)
    , m_canMoveVert(canMoveVert)
{

}

HudJoystickButton::HudJoystickButton(const HudJoystickButton& other)
    : HudButton(other)
    , m_radius(other.m_radius)
    , m_sqrRadius(other.m_sqrRadius)
    , m_canMoveHorz(other.m_canMoveHorz)
    , m_canMoveVert(other.m_canMoveVert)
{
}

HudJoystickButton::~HudJoystickButton()
{
}

void HudJoystickButton::appear(HudButtonListener* listener)
{
    HudButton::appear(listener);
    m_direction.clear();
    Core::touchManager().addListener(this);
}

void HudJoystickButton::disappear()
{
    HudButton::disappear();
    Core::touchManager().removeListener(this);
}

void HudJoystickButton::draw()
{
    if (m_animation == HUD_HIDE)
        return;
    
    glPushMatrix();
    if (m_selected)
        glTranslatef(m_appearedPos[0], m_appearedPos[1], m_appearedPos[2]);
    else
        glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    m_overMesh->draw(1);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(m_canMoveHorz ? m_pos[0] : m_appearedPos[0], m_canMoveVert ? m_pos[1] : m_appearedPos[1], m_pos[2] + 0.1);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    m_mesh->draw(1);
	glPopMatrix();
}

void HudJoystickButton::touchesBegan(const std::map<int, Touch>& touches)
{
    std::map<int, Touch>::const_iterator it = touches.begin();
    while (!isSelected() && it != touches.end()) {
        const Touch& t = it->second;
        if (! t.used()) {
            const Vector4 diff = t.pos() - m_appearedPos;
            double sl = diff.sqrlen();
            if (sl >= m_sqrRadius * 16) {
                // Nothing
            } else if (sl >= m_sqrRadius) {
                t.setUsed();
                m_touchId = it->first;
                m_direction = diff.normalize();
                m_pos = m_appearedPos + m_direction * m_radius;
                select();
            } else {
                t.setUsed();
                m_touchId = it->first;
                m_pos = it->second.pos();
                m_direction = diff * 1. / m_radius;
                select();
            }            
        }
        it++;
    }
}

void HudJoystickButton::touchesMoved(const std::map<int, Touch>& touches)
{
    if (! isSelected())
        return;
    
    std::map<int, Touch>::const_iterator found = touches.find(m_touchId);
    if (found == touches.end() || found->second.used())
        return;
    
    const Touch& t = found->second;
    const Vector4 diff = t.pos() - m_appearedPos;
    double sl = diff.sqrlen();
    if (sl >= m_sqrRadius * 16) {
        m_pos = m_appearedPos;
        m_direction.clear();
    } else if (sl >= m_sqrRadius) {
        m_direction = diff.normalize();
        m_pos = m_appearedPos + m_direction * m_radius;
    } else {
        m_direction = diff * 1./ m_radius;
        m_pos = found->second.pos();
    }
    found->second.setUsed();
}

void HudJoystickButton::touchesEnded(const std::map<int, Touch>& touches)
{
    if (! isSelected())
        return;
    
    std::map<int, Touch>::const_iterator found = touches.find(m_touchId);
    if (found == touches.end() || found->second.used())
        return;
    
    m_pos = m_appearedPos;
    release();
    found->second.setUsed();
    m_direction.clear();
}

void HudJoystickButton::touchesCancelled(const std::map<int, Touch>& touches)
{
    if (! isSelected())
        return;
    
    std::map<int, Touch>::const_iterator found = touches.find(m_touchId);
    if (found == touches.end() || found->second.used())
        return;
    
    m_pos = m_appearedPos;
    release();
    found->second.setUsed();
    m_direction.clear();
}
