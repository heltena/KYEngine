#include <KYEngine/Entity.h>
#include <KYEngine/Private/Hits/HitParabolicTransform.h>

HitParabolicTransform::HitParabolicTransform(const Vector4& from, const Vector4& direction, double upZ, double downZ, double duration, double mass, const Vector4& gravity)
    : m_from(from)
    , m_direction(direction)
    , m_upZ(upZ)
    , m_downZ(downZ)
    , m_duration(duration)
    , m_mass(mass)
    , m_gravity(gravity)
{
    // p = from + d * t + g * t ^ 2
    // d(p)/dt = d + 2gt + dt
    m_inflection = - m_direction[1] / (2 * m_gravity[1]);
}

HitParabolicTransform::~HitParabolicTransform()
{
}

void HitParabolicTransform::updateTransform(Entity* entity, double percent)
{
    double t = percent * m_duration;
    Vector4 newPos = m_from + m_direction * t + m_gravity * (t * t) * m_mass;
    newPos[3] = 1;
    if (t < m_inflection)
        newPos[2] = m_upZ;
    else
        newPos[2] = m_downZ;
    entity->setPos(newPos);
}