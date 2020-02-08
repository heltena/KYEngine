#pragma once

#include <KYEngine/Utility/Vector4.h>

class ParticleInfo
{
public:
    ParticleInfo();
    virtual ~ParticleInfo();
    
public:
    void init(const Vector4& initialPos, const Vector4& vel, double scale, double scaleVel, double initialAlpha, double alphaVel, double timeout, double initialAngle, double initialAngularVel);
    
public:
    const Vector4& pos() const { return m_pos; }
    const Vector4& vel() const { return m_vel; }
    double scale() const { return m_scale; }
    double scaleVel() const { return m_scaleVel; }
    double alpha() const { return m_alpha; }
    double alphaVel() const { return m_alphaVel; }
    double timeout() const { return m_timeout; }
    double angle() const { return m_angle; }
    double angularVel() const { return m_angularVel; }

public:
    bool isFinished() const { return m_timeout <= 0; }
    void update(const double elapsedTime);
    
private:
    Vector4 m_pos;
    Vector4 m_vel;
    double m_scale;
    double m_scaleVel;
    double m_alpha;
    double m_alphaVel;
    double m_timeout;
    double m_angle;
    double m_angularVel;
};