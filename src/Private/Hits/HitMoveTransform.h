#pragma once

#include <KYEngine/HitTransform.h>
#include <KYEngine/Utility/Vector4.h>

class Entity;

class HitMoveTransform
    : public HitTransform
{
public:
    HitMoveTransform(const Vector4& from, const Vector4& to, double accelMagnitude);
    virtual ~HitMoveTransform();
        
// HitTransform implementation
public:
    virtual void updateTransform(Entity* entity, double percent);

private:
    Vector4 m_from;
    Vector4 m_to;
    double m_accelMagnitude;
};
