#include <KYEngine/Utility/Blackouter.h>
#include <KYEngine/Utility/KYMath.h>

Blackouter::Blackouter()
    : m_running(false)
    , m_entity(NULL)
{
}

Blackouter::~Blackouter()
{
}

void Blackouter::start(Entity* entity, bool onlyAlpha, double duration, double frequency, double offset)
{
    if (m_running)
        stop();

    m_running = true;
    m_entity = entity;
    m_onlyAlpha = onlyAlpha;
    m_initialColor = m_entity->color();
    m_elapsedTime = 0;
    m_duration = duration;
    m_frequency = frequency;
}

void Blackouter::stop()
{
    if (! m_running)
        return;
    if (m_entity) {
        m_entity->setColor(m_initialColor);
        m_entity = NULL;
    }
    m_running = false;
}

void Blackouter::update(const double elapsedTime)
{
    m_elapsedTime += elapsedTime;
    
    if (m_elapsedTime >= m_duration) {
        stop();
        return;
    }
    
    double value = Math::sin(m_elapsedTime * m_frequency + m_offset);
    Vector4 newColor = m_onlyAlpha ? m_initialColor : Vector4::WHITE;
    newColor[3] = value;
    
    m_entity->setColor(newColor);
}