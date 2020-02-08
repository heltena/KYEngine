#pragma once

#include <KYEngine/HitTransform.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class HitTransformFactory
{
private:
    HitTransformFactory();

public:
    static HitTransform* createHitMoveTransform(const Vector4& from, const Vector4& to, double accelMagnitude);
    static HitTransform* createHitParabolicTransform(const Vector4& from, const Vector4& direction, double upZ, double downZ, double duration, double mass, const Vector4& gravity = Vector4::GRAVITY);
};