#include <KYEngine/Entity.h>
#include <KYEngine/PrivatE/Hits/HitMoveTransform.h>

HitMoveTransform::HitMoveTransform(const Vector4& from, const Vector4& to, double accelMagnitude)
    : m_from(from)
    , m_to(to)
    , m_accelMagnitude(accelMagnitude)
{
}

HitMoveTransform::~HitMoveTransform()
{
}

void HitMoveTransform::updateTransform(Entity* entity, double percent)
{
    entity->setPos(Vector4::interpolate(m_from, m_to, percent, m_accelMagnitude));
}
