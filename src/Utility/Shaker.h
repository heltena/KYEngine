#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Utility/Vector4.h>

class Shaker
{
public:
    Shaker();
    virtual ~Shaker();
    
public:
    bool isFinished() const { return ! m_shaking; }

public:
    void start(Entity* entity, double timeout, double magnitude, double angle = 0, double offset = M_PI * 2, const Vector4& scale = Vector4::WHITE);
    void stop();
    void update(const double elapsedTime);

private:
    bool m_shaking;
    Entity* m_entity;
    Vector4 m_initialPos;
    Vector4 m_initialScale;
    Vector4 m_scale;
    double m_timeout;
    double m_magnitude;
    double m_angle;
    double m_offset;
};