#include <KYEngine/Private/Huds/HudProgressView.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

HudProgressView::HudProgressView()
    : m_layer(NULL)
{
}

HudProgressView::HudProgressView(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, const Vector4& offset, double animDuration, double accelMagnitude, double minValue, double maxValue, double initialValue, bool ltr, double angle, Mesh* backgroundMesh, Mesh* mesh)
    : m_layer(NULL)
    , m_id(id)
    , m_name(name)
    , m_appearedPos(appearedPos)
    , m_disappearedPos(disappearedPos)
    , m_pos(disappearedPos)
    , m_offset(offset)
    , m_animDuration(animDuration)
    , m_accelMagnitude(accelMagnitude)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_initialValue(initialValue)
    , m_ltr(ltr)
    , m_angle(angle)
    , m_currentValue(initialValue)
    , m_animation(HUD_HIDE)
    , m_elapsedTime(0)
    , m_backgroundMesh(backgroundMesh)
    , m_mesh(mesh)
    , m_hpercent(1)
    , m_color(1.0f, 1.0f, 1.0f, 1.0f)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
{
    setCurrentValue(m_initialValue);
}

HudProgressView::HudProgressView(const HudProgressView& other)
    : m_layer(other.m_layer)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_offset(other.m_offset)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_minValue(other.m_minValue)
    , m_maxValue(other.m_maxValue)
    , m_initialValue(other.m_initialValue)
    , m_ltr(other.m_ltr)
    , m_angle(other.m_angle)
    , m_currentValue(other.m_currentValue)
    , m_animation(other.m_animation)
    , m_elapsedTime(other.m_elapsedTime)
    , m_id(other.m_id)
    , m_name(other.m_name)
    , m_backgroundMesh(other.m_backgroundMesh)
    , m_mesh(other.m_mesh)
    , m_pos(other.m_pos)
    , m_bounds(other.m_bounds)
    , m_color(other.m_color)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    , m_fromPos(other.m_fromPos)
    , m_toPos(other.m_toPos)
{
}

HudProgressView::~HudProgressView()
{
}

void HudProgressView::appear()
{
    setCurrentValue(m_initialValue);
    m_fromPos = m_pos;
    m_toPos = m_appearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_APPEARING;
}

bool HudProgressView::isAppeared() const
{
    return m_animation == HUD_SHOWING;
}

void HudProgressView::disappear()
{
    m_fromPos = m_pos;
    m_toPos = m_disappearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_DISAPPEARING;
}

bool HudProgressView::isDisappeared() const
{
    return m_animation == HUD_HIDE;
}

void HudProgressView::setCurrentValue(double currentValue)
{
    m_valueNormalized = (currentValue - m_minValue) / (m_maxValue - m_minValue);
    if (m_valueNormalized < 0)
        m_valueNormalized = 0;
    else if (m_valueNormalized > 1)
        m_valueNormalized = 1;
    if (!m_ltr)
        m_valueNormalized = -m_valueNormalized;
}

void HudProgressView::update(const double elapsedTime)
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

void HudProgressView::draw()
{
    if (m_animation == HUD_HIDE)
        return;
    
    glPushMatrix();
    glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    m_backgroundMesh->draw(1);
    glTranslatef(m_offset[0], m_offset[1], m_offset[2] + 0.01);
    m_mesh->draw(m_valueNormalized);
    
	glPopMatrix();
}
