#include <KYEngine/Private/Huds/HudMapView.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>

HudMapView::HudMapView()
    : m_layer(NULL)
{
}

HudMapView::HudMapView(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, const Vector4&offset, double animDuration, double accelMagnitude, double width, double minValue, double maxValue, Mesh* backgroundMesh, Mesh* mesh, Mesh* centerMesh)
    : m_layer(NULL)
    , m_id(id)
    , m_name(name)
    , m_appearedPos(appearedPos)
    , m_disappearedPos(disappearedPos)
    , m_pos(disappearedPos)
    , m_offset(offset)
    , m_animDuration(animDuration)
    , m_accelMagnitude(accelMagnitude)
    , m_width(width)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_animation(HUD_HIDE)
    , m_elapsedTime(0)
    , m_backgroundMesh(backgroundMesh)
    , m_mesh(mesh)
    , m_centerMesh(centerMesh)
    , m_hpercent(1)
    , m_color(1.0f, 1.0f, 1.0f, 1.0f)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
{
}

HudMapView::HudMapView(const HudMapView& other)
    : m_layer(other.m_layer)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_offset(other.m_offset)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_width(other.m_width)
    , m_minValue(other.m_minValue)
    , m_maxValue(other.m_maxValue)
    , m_animation(other.m_animation)
    , m_elapsedTime(other.m_elapsedTime)
    , m_id(other.m_id)
    , m_name(other.m_name)
    , m_backgroundMesh(other.m_backgroundMesh)
    , m_mesh(other.m_mesh)
    , m_centerMesh(other.m_centerMesh)
    , m_pos(other.m_pos)
    , m_bounds(other.m_bounds)
    , m_color(other.m_color)
    , m_angle(other.m_angle)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    , m_fromPos(other.m_fromPos)
    , m_toPos(other.m_toPos)
    , m_itemTypes(other.m_itemTypes)
    , m_items(other.m_items)
{
}

HudMapView::~HudMapView()
{
}

void HudMapView::appear()
{
    m_fromPos = m_pos;
    m_toPos = m_appearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_APPEARING;
    
    m_items.clear();
}

bool HudMapView::isAppeared() const
{
    return m_animation == HUD_SHOWING;
}

void HudMapView::disappear()
{
    m_fromPos = m_pos;
    m_toPos = m_disappearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_DISAPPEARING;
}

bool HudMapView::isDisappeared() const
{
    return m_animation == HUD_HIDE;
}

void HudMapView::update(const double elapsedTime)
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

void HudMapView::addItemType(int id, Mesh* leftMesh, Mesh* rightMesh)
{
    m_itemTypes[id] = HudMapViewItemType(id, leftMesh, rightMesh);
}

void HudMapView::draw()
{
    if (m_animation == HUD_HIDE)
        return;
    
    glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    m_backgroundMesh->draw(1);
    
    glPushMatrix();
    glTranslatef(m_offset[0], m_offset[1], m_offset[2] + 0.001);
    m_mesh->draw(1);
    glPopMatrix();
    
    glTranslatef(0, 0, 0.001);
    
    if (m_centerMesh) {
        glTranslatef(0, 0, 0.001);
        m_centerMesh->draw(1);
    }
    
    for(std::list<HudMapViewItem>::iterator it = m_items.begin(); it != m_items.end(); it++) {
        const double& pos = it->pos();
        if (pos >= m_minValue && pos <= m_maxValue) {
            glTranslatef(0, 0, 0.001);
            double normalize = ((pos - m_minValue) / (m_maxValue - m_minValue) - 0.5) * m_width;
            glPushMatrix();
            glTranslatef(normalize, 0.0, 0.0);

            DirectionEnum toDraw;
            if (it->direction() == DIRECTION_ZERO) {
                toDraw = normalize > 0 ? DIRECTION_LEFT : DIRECTION_RIGHT;
            } else
                toDraw = it->direction();
            
            if (toDraw == DIRECTION_LEFT)
                m_itemTypes[it->type()].leftMesh()->draw(1);
            else
                m_itemTypes[it->type()].rightMesh()->draw(1);
            glPopMatrix();
        }
    }
    
	glPopMatrix();
}

