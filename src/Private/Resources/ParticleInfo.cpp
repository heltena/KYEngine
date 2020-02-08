#include <KYEngine/Private/Resources/ParticleInfo.h>

ParticleInfo::ParticleInfo()
    : m_alpha(0)
    , m_alphaVel(0)
    , m_timeout(0)
    , m_angle(0)
    , m_angularVel(0)
{
}

ParticleInfo::~ParticleInfo()
{
}

void ParticleInfo::init(const Vector4& initialPos, const Vector4& vel, double scale, double scaleVel, double initialAlpha, double alphaVel, double timeout, double initialAngle, double initialAngularVel)
{
    m_pos = initialPos;
    m_vel = vel;
    m_scale = scale;
    m_scaleVel = scaleVel;
    m_alpha = initialAlpha;
    m_alphaVel = alphaVel;
    m_timeout = timeout;
    m_angle = initialAngle;
    m_angularVel = initialAngularVel;
}

void ParticleInfo::update(const double elapsedTime)
{
    m_timeout -= elapsedTime;
    if (m_timeout < 0)
        return;
    
    m_pos += m_vel * elapsedTime;
    m_scale += m_scaleVel * elapsedTime;
    m_alpha += m_alphaVel * elapsedTime;
    m_angle += m_angularVel * elapsedTime;
}