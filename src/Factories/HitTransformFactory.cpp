#include <KYEngine/Factories/HitTransformFactory.h>

#include <KYEngine/Private/Hits/HitMoveTransform.h>
#include <KYEngine/Private/Hits/HitParabolicTransform.h>

HitTransformFactory::HitTransformFactory()
{
}

HitTransform* HitTransformFactory::createHitMoveTransform(const Vector4& from, const Vector4& to, double accelMagnitude)
{
    return new HitMoveTransform(from, to, accelMagnitude);
}

HitTransform* HitTransformFactory::createHitParabolicTransform(const Vector4& from, const Vector4& direction, double upZ, double downZ, double duration, double mass, const Vector4& gravity)
{
    return new HitParabolicTransform(from, direction, upZ, downZ, duration, mass, gravity);
}