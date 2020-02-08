#include <KYEngine/Managers/ParticleEmitterInfo.h>

ParticleEmitterInfo::ParticleEmitterInfo()
    : m_emitter(NULL)
    , m_follow(false)
    , m_followEntity(NULL)
    , m_layer(NULL)
{
}

ParticleEmitterInfo::ParticleEmitterInfo(ParticleEmitterExtension* emitter, RenderLayer* layer)
    : m_emitter(emitter)
    , m_follow(false)
    , m_followEntity(NULL)
    , m_layer(layer)
{
}

ParticleEmitterInfo::ParticleEmitterInfo(ParticleEmitterExtension* emitter, Entity* followEntity, const Vector4& offset, RenderLayer* layer)
    : m_emitter(emitter)
    , m_follow(true)
    , m_followEntity(followEntity)
    , m_offset(offset)
    , m_layer(layer)
{
}

ParticleEmitterInfo::ParticleEmitterInfo(const ParticleEmitterInfo& other)
    : m_emitter(other.m_emitter)
    , m_follow(other.m_follow)
    , m_followEntity(other.m_followEntity)
    , m_offset(other.m_offset)
    , m_layer(other.m_layer)
{
}

ParticleEmitterInfo::~ParticleEmitterInfo()
{
}
