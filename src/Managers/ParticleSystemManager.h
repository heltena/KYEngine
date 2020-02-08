#pragma once

#include <KYEngine/Managers/ParticleEmitterInfo.h>
#include <KYEngine/Utility/Vector4.h>

#include <map>
#include <string>

class Core;
class ParticleEmitterExtension;
class RenderLayer;

class ParticleSystemManager
{
private:
    static const std::string RENDER_LAYER_NAME;
    static const int RENDER_LAYER_ZORDER;
    
private:
    friend class Core;
    ParticleSystemManager();
    virtual ~ParticleSystemManager();
    
public:
    void init();
    void done();
    
public:
    int newParticleEmitter(const Vector4& pos, const std::string& name, RenderLayer* layer = NULL);
    int newParticleEmitter(const Vector4& pos, const std::string& name, double timeout, RenderLayer* layer = NULL);
    int newParticleEmitter(Entity* followEntity, const Vector4& offset, const std::string& name, RenderLayer* layer = NULL);
    int newParticleEmitter(Entity* followEntity, const Vector4& offset, const std::string& name, double timeout, RenderLayer* layer = NULL);
    void removeParticleEmitter(int id);
    void removeAllParticleEmitters();
    void pauseParticleEmitter(int id);
    void resumeParticleEmitter(int id);
    void pauseAllParticleEmitters();
    void resumeAllParticleEmitters();
    void resumeAllParticleEmittersPausedByManager();
    bool particleEmitterExists(int id) const;  
    const Vector4 particleEmitterPos(int id) const;
    void updatePos(int id, const Vector4& pos);
    void update(const double elapsedTime);

private:
    RenderLayer* m_layer;
    int m_nextId;
    std::map<int, ParticleEmitterInfo> m_particleEmitters;
    std::set<int> m_particleEmittersPausedByManager;
};