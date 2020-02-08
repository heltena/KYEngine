#include <KYEngine/Private/Huds/HudFaceView.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>

HudFaceView::HudFaceView()
    : m_layer(NULL)
{
}

HudFaceView::HudFaceView(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, double minValue, double maxValue, double initialValue)
    : m_layer(NULL)
    , m_id(id)
    , m_name(name)
    , m_appearedPos(appearedPos)
    , m_disappearedPos(disappearedPos)
    , m_pos(disappearedPos)
    , m_animDuration(animDuration)
    , m_accelMagnitude(accelMagnitude)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_initialValue(initialValue)
    , m_currentValue(initialValue)
    , m_animation(HUD_HIDE)
    , m_elapsedTime(0)
    , m_hpercent(1)
    , m_color(1.0f, 1.0f, 1.0f, 1.0f)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
{
}

HudFaceView::HudFaceView(const HudFaceView& other)
    : m_layer(other.m_layer)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_minValue(other.m_minValue)
    , m_maxValue(other.m_maxValue)
    , m_initialValue(other.m_initialValue)
    , m_currentValue(other.m_currentValue)
    , m_animation(other.m_animation)
    , m_elapsedTime(other.m_elapsedTime)
    , m_id(other.m_id)
    , m_name(other.m_name)
    , m_pos(other.m_pos)
    , m_bounds(other.m_bounds)
    , m_color(other.m_color)
    , m_angle(other.m_angle)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    , m_fromPos(other.m_fromPos)
    , m_toPos(other.m_toPos)
    , m_states(other.m_states)
{
    setCurrentValue(m_initialValue);
}

HudFaceView::~HudFaceView()
{
}

void HudFaceView::addState(double forLessThan, Mesh* mesh)
{
    m_states[forLessThan] = mesh;
}

void HudFaceView::appear()
{
    setCurrentValue(m_initialValue);
    m_fromPos = m_pos;
    m_toPos = m_appearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_APPEARING;
}

bool HudFaceView::isAppeared() const
{
    return m_animation == HUD_SHOWING;
}

void HudFaceView::disappear()
{
    m_fromPos = m_pos;
    m_toPos = m_disappearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_DISAPPEARING;
}

bool HudFaceView::isDisappeared() const
{
    return m_animation == HUD_HIDE;
}

void HudFaceView::setCurrentValue(double currentValue)
{
    m_currentValue = currentValue;
}

void HudFaceView::update(const double elapsedTime)
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

void HudFaceView::draw()
{
    if (m_animation == HUD_HIDE)
        return;
    
    glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    // TODO: rotate!
    bool found = false;
    std::map<double, Mesh*>::iterator it = m_states.begin();
    while (! found && it != m_states.end()) {
        if (it->first >= m_currentValue) {
            found = true;
            it->second->draw(1);
        } else
            it++;
    }

	glPopMatrix();
}
