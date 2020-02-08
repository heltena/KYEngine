#include <KYEngine/Core.h>
#include <KYEngine/ParticleEmitterExtension.h>
#include <KYEngine/Managers/ParticleSystemManager.h>
#include <KYEngine/RenderLayer.h>

const std::string ParticleSystemManager::RENDER_LAYER_NAME = "#particleSystem";
const int ParticleSystemManager::RENDER_LAYER_ZORDER = 10;

ParticleSystemManager::ParticleSystemManager()
    : m_layer(NULL)
    , m_nextId(0)
{
}

ParticleSystemManager::~ParticleSystemManager()
{
}

void ParticleSystemManager::init()
{
    m_layer = Core::renderManager().createLayer(RENDER_LAYER_NAME, RENDER_LAYER_ZORDER);
    m_nextId = 0;
}

void ParticleSystemManager::done()
{
    Core::renderManager().removeLayer(RENDER_LAYER_NAME);
}

int ParticleSystemManager::newParticleEmitter(const Vector4& pos, const std::string& name, RenderLayer* layer)
{
    if (layer == NULL)
        layer = m_layer;
    int id = m_nextId++;
    Entity* entity = Core::resourceManager().entity(name);
    ParticleEmitterExtension* newEmitter = entity->particleEmitterInterface()->clone();
    m_particleEmitters[id] = ParticleEmitterInfo(newEmitter, layer);
    newEmitter->start(pos);
    layer->addEntity(newEmitter->entity());
    m_particleEmittersPausedByManager.erase(id);
    return id;
}

int ParticleSystemManager::newParticleEmitter(const Vector4& pos, const std::string& name, double timeout, RenderLayer* layer)
{
    if (layer == NULL)
        layer = m_layer;
    int id = m_nextId++;
    Entity* entity = Core::resourceManager().entity(name);
    ParticleEmitterExtension* newEmitter = entity->particleEmitterInterface()->clone();
    m_particleEmitters[id] = ParticleEmitterInfo(newEmitter, layer);
    newEmitter->start(timeout, pos);
    layer->addEntity(newEmitter->entity());
    m_particleEmittersPausedByManager.erase(id);
    return id;
}

int ParticleSystemManager::newParticleEmitter(Entity* followEntity, const Vector4& offset, const std::string& name, RenderLayer* layer)
{
    if (layer == NULL)
        layer = m_layer;
    int id = m_nextId++;
    Entity* entity = Core::resourceManager().entity(name);
    ParticleEmitterExtension* newEmitter = entity->particleEmitterInterface()->clone();
    m_particleEmitters[id] = ParticleEmitterInfo(newEmitter, followEntity, offset, layer);
    newEmitter->start(followEntity->pos());
    layer->addEntity(newEmitter->entity());
    m_particleEmittersPausedByManager.erase(id);
    return id;
}

int ParticleSystemManager::newParticleEmitter(Entity* followEntity, const Vector4& offset, const std::string& name, double timeout, RenderLayer* layer)
{
    if (layer == NULL)
        layer = m_layer;
    int id = m_nextId++;
    Entity* entity = Core::resourceManager().entity(name);
    ParticleEmitterExtension* newEmitter = entity->particleEmitterInterface()->clone();
    m_particleEmitters[id] = ParticleEmitterInfo(newEmitter, followEntity, offset, layer);
    newEmitter->start(timeout, followEntity->pos());
    layer->addEntity(newEmitter->entity());
    m_particleEmittersPausedByManager.erase(id);
    return id;
}

void ParticleSystemManager::removeParticleEmitter(int id)
{
    std::map<int, ParticleEmitterInfo>::iterator found = m_particleEmitters.find(id);
    if (found == m_particleEmitters.end())
        return;
    ParticleEmitterExtension* emitter = found->second.emitter();
    found->second.layer()->removeEntity(emitter->entity());
    delete emitter;
    m_particleEmitters.erase(found);
    m_particleEmittersPausedByManager.erase(id);
}

void ParticleSystemManager::removeAllParticleEmitters()
{
    for(std::map<int, ParticleEmitterInfo>::iterator it = m_particleEmitters.begin(); it != m_particleEmitters.end(); it++) {
        ParticleEmitterExtension* emitter = it->second.emitter();
        it->second.layer()->removeEntity(emitter->entity());
        delete emitter;
    }
    m_particleEmitters.clear();
    m_particleEmittersPausedByManager.clear();
}

void ParticleSystemManager::pauseParticleEmitter(int id)
{
    std::map<int, ParticleEmitterInfo>::iterator found = m_particleEmitters.find(id);
    if (found == m_particleEmitters.end())
        return;
    ParticleEmitterExtension* emitter = found->second.emitter();
    emitter->pause();
    m_particleEmittersPausedByManager.erase(id);
}

void ParticleSystemManager::resumeParticleEmitter(int id)
{
    std::map<int, ParticleEmitterInfo>::iterator found = m_particleEmitters.find(id);
    if (found == m_particleEmitters.end())
        return;
    ParticleEmitterExtension* emitter = found->second.emitter();
    emitter->resume();
    m_particleEmittersPausedByManager.erase(id);
}

void ParticleSystemManager::pauseAllParticleEmitters()
{
    for(std::map<int, ParticleEmitterInfo>::iterator it = m_particleEmitters.begin(); it != m_particleEmitters.end(); it++) {
        ParticleEmitterExtension* emitter = it->second.emitter();
        if (! emitter->isPaused()) {
            emitter->pause();
            m_particleEmittersPausedByManager.insert(it->first);
        }
    }
}

void ParticleSystemManager::resumeAllParticleEmitters()
{
    for(std::map<int, ParticleEmitterInfo>::iterator it = m_particleEmitters.begin(); it != m_particleEmitters.end(); it++) {
        ParticleEmitterExtension* emitter = it->second.emitter();
        if (! emitter->isPaused())
            emitter->resume();
    }
    m_particleEmittersPausedByManager.clear();
}

void ParticleSystemManager::resumeAllParticleEmittersPausedByManager()
{
    for(std::set<int>::iterator it = m_particleEmittersPausedByManager.begin(); it != m_particleEmittersPausedByManager.end(); it++) {
        std::map<int, ParticleEmitterInfo>::iterator found = m_particleEmitters.find(*it);
        if (found != m_particleEmitters.end()) {
            ParticleEmitterExtension* emitter = found->second.emitter();
            emitter->resume();
        }
    }
    m_particleEmittersPausedByManager.clear();
}

bool ParticleSystemManager::particleEmitterExists(int id) const
{
    std::map<int, ParticleEmitterInfo>::const_iterator found = m_particleEmitters.find(id);
    return found != m_particleEmitters.end();
}

const Vector4 ParticleSystemManager::particleEmitterPos(int id) const
{
    std::map<int, ParticleEmitterInfo>::const_iterator found = m_particleEmitters.find(id);
    if (found == m_particleEmitters.end())
        return Vector4();
    
    ParticleEmitterExtension* emitter = found->second.emitter();
    return emitter->entity()->pos();
}
    
void ParticleSystemManager::updatePos(int id, const Vector4& pos)
{
    std::map<int, ParticleEmitterInfo>::iterator found = m_particleEmitters.find(id);
    if (found == m_particleEmitters.end())
        return;
    if (found->second.follow())
        return;
    ParticleEmitterExtension* emitter = found->second.emitter();
    emitter->entity()->setPos(pos);
}

void ParticleSystemManager::update(const double elapsedTime)
{
    std::map<int, ParticleEmitterInfo>::iterator it = m_particleEmitters.begin();
    while (it != m_particleEmitters.end()) {
        ParticleEmitterExtension* emitter = it->second.emitter();
        
        if (emitter->isFinished()) {
            std::map<int, ParticleEmitterInfo>::iterator toKill = it++;
            toKill->second.layer()->removeEntity(emitter->entity());
            delete emitter;
            m_particleEmitters.erase(toKill);
        } else {
            if (it->second.follow())
                emitter->entity()->setPos(it->second.followEntity()->pos() + it->second.offset());
            emitter->update(elapsedTime);
            it++; 
        }
    }
}