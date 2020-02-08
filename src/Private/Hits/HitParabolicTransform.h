#pragma once

#include <KYEngine/HitTransform.h>
#include <KYEngine/Utility/Vector4.h>

class Entity;

class HitParabolicTransform
    : public HitTransform
{
public:
    HitParabolicTransform(const Vector4& from, const Vector4& direction, double upZ, double downZ, double duration, double mass, const Vector4& gravity = Vector4::GRAVITY);
    virtual ~HitParabolicTransform();
        
// HitTransform implementation
public:
    virtual void updateTransform(Entity* entity, double percent);

private:
    Vector4 m_from;
    Vector4 m_direction;
    double m_upZ;
    double m_downZ;
    double m_duration;
    double m_mass;
    double m_inflection;
    Vector4 m_gravity;
};
