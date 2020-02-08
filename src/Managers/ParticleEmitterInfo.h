#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/ParticleEmitterExtension.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/Utility/Vector4.h>

class ParticleEmitterInfo
{
public:
    ParticleEmitterInfo();
    ParticleEmitterInfo(ParticleEmitterExtension* emitter, RenderLayer* layer);
    ParticleEmitterInfo(ParticleEmitterExtension* emitter, Entity* followEntity, const Vector4& offset, RenderLayer* layer);
    ParticleEmitterInfo(const ParticleEmitterInfo& other);
    virtual ~ParticleEmitterInfo();
    
public:
    ParticleEmitterExtension* emitter() const { return m_emitter; }
    bool follow() const { return m_follow; }
    Entity* followEntity() const { return m_followEntity; }
    const Vector4& offset() const { return m_offset; }
    RenderLayer* layer() const { return m_layer; }

private:
    ParticleEmitterExtension* m_emitter;
    bool m_follow;
    Entity* m_followEntity;
    Vector4 m_offset;
    RenderLayer* m_layer;
};