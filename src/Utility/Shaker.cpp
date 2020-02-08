#include <KYEngine/Utility/Shaker.h>

#include <iostream>

Shaker::Shaker()
    : m_shaking(false)
    , m_entity(NULL)
    , m_timeout(0)
    , m_angle(0)
    , m_offset(M_PI * 2)
{
}

Shaker::~Shaker()
{
}

void Shaker::start(Entity* entity, double timeout, double magnitude, double angle, double offset, const Vector4& scale)
{
    if (m_shaking)
        stop();
    m_shaking = true;
    m_entity = entity;
    m_initialPos = m_entity->pos();
    m_initialScale = m_entity->scale();
    for(int i = 0; i < 3; i++)
        m_scale[i] = m_initialScale[i] * scale[i];
    m_scale[3] = 1;
    m_timeout = timeout;
    m_magnitude = magnitude;
    m_angle = angle;
    m_offset = offset;
}

void Shaker::stop()
{
    if (m_entity) {
        m_entity->setPos(m_initialPos);
        m_entity->setScale(m_initialScale);
        m_entity = NULL;
    }
    m_shaking = false;
}

void Shaker::update(const double elapsedTime)
{
    if (!m_shaking)
        return;
        
    m_timeout -= elapsedTime;
    if (m_timeout <= 0)
        stop();
    else {
        double angle = Math::randomWithOffset(m_angle, m_offset);
        Vector4 offset = Vector4::fromPolar2D(angle, m_magnitude);
        m_entity->setPos(m_initialPos + offset);
        m_entity->setScale(m_scale);
    }
}
