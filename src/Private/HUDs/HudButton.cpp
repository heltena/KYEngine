#include <KYEngine/Private/Huds/HudButton.h>
#include <KYEngine/Private/Huds/HudButtonListener.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

HudButton::HudButton()
    : m_layer(NULL)
    , m_id(0)
{
}

HudButton::HudButton(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, Mesh* mesh, Mesh* overMesh)
    : m_layer(NULL)
    , m_appearedPos(appearedPos)
    , m_disappearedPos(disappearedPos)
    , m_pos(disappearedPos)
    , m_animation(HUD_HIDE)
    , m_animDuration(animDuration)
    , m_accelMagnitude(accelMagnitude)
    , m_selected(false)
    , m_id(id)
    , m_name(name)
    , m_hpercent(1)
    , m_color(1.0f, 1.0f, 1.0f, 1.0f)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
    , m_listener(NULL)
    , m_mesh(mesh)
    , m_overMesh(overMesh)
{
}

HudButton::HudButton(const HudButton& other)
    : m_layer(other.m_layer)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_animation(other.m_animation)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_selected(other.m_selected)
    , m_id(other.m_id)
    , m_name(other.m_name)
    , m_color(other.m_color)
    , m_angle(other.m_angle)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    , m_listener(other.m_listener)
    , m_mesh(other.m_mesh)
    , m_overMesh(other.m_overMesh)
    , m_elapsedTime(other.m_elapsedTime)
    , m_pos(other.m_pos)
    , m_bounds(other.m_bounds)
    , m_fromPos(other.m_fromPos)
    , m_toPos(other.m_toPos)
{
}

HudButton::~HudButton()
{
    
}

void HudButton::appear(HudButtonListener* listener)
{
    m_listener = listener;
    m_selected = false;
    m_fromPos = m_pos;
    m_toPos = m_appearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_APPEARING;
}

bool HudButton::isAppeared() const
{
    return m_animation == HUD_SHOWING;
}

void HudButton::disappear()
{
    m_fromPos = m_pos;
    m_toPos = m_disappearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_DISAPPEARING;
}

bool HudButton::isDisappeared() const
{
    return m_animation == HUD_HIDE;
}

void HudButton::update(const double elapsedTime)
{
    if (m_animation == HUD_HIDE || m_animation == HUD_SHOWING)
        return;
    
    m_elapsedTime += elapsedTime;
    m_pos = Vector4::interpolate(m_fromPos, m_toPos, m_elapsedTime / m_animDuration, m_accelMagnitude);
    
    if (m_elapsedTime > m_animDuration) {
        if (m_animation == HUD_APPEARING)
            m_animation = HUD_SHOWING;
        else
            m_animation = HUD_HIDE;
        m_pos = m_toPos;
    }
}

void HudButton::draw()
{
    if (m_animation == HUD_HIDE)
        return;
    
    glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    if (m_selected && m_overMesh != NULL)
        m_overMesh->draw(1);
    else if (m_mesh != NULL)
        m_mesh->draw(1);
	glPopMatrix();
}

void HudButton::select()
{
    m_selected = true;
    if (m_listener)
        m_listener->hudButtonPressed(m_id);
}

void HudButton::release()
{
    m_selected = false;
    if (m_listener)
        m_listener->hudButtonReleased(m_id);
}

