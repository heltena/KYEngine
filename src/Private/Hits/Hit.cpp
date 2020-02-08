#include <KYEngine/Entity.h>
#include <KYEngine/HitTransform.h>
#include <KYEngine/RenderLayer.h>

#include <KYEngine/Private/Hits/Hit.h>
#include <KYEngine/Private/Resources/AnimMeshEntityResource.h>
#include <KYEngine/Private/Resources/EntityResource.h>

Hit::Hit()
    : m_layer(NULL)
    , m_entity(NULL)
    , m_timeout(0)
    , m_duration(0)
{
}

Hit::~Hit()
{
    done();
}

void Hit::init(RenderLayer* layer, const Vector4& pos, double duration, const std::string& animMeshCollectionRef, const std::string& animRef, double delay, HitTransform* transform, bool controlTransformLifeCycle)
{
    m_transform = transform;
    m_controlTransformLifeCycle = controlTransformLifeCycle;
    m_layer = layer;
    m_duration = duration;

    if (delay == 0) {
        m_state = SHOWING;
        m_timeout = duration;
    } else {
        m_state = APPEAR;
        m_timeout = delay;
    }
    AnimMeshEntityResource* entity = new AnimMeshEntityResource();
    entity->setAnimMeshCollectionRef(animMeshCollectionRef);
    entity->load();
    entity->setAnim(animRef);
    entity->setUseBlending(true);
    m_entity = entity;
    
    m_entity->setPos(pos);
    m_entity->setUseBlending(true);
    m_layer->addEntity(m_entity, true);
    if (m_transform)
        m_transform->updateTransform(m_entity, 0);
}

void Hit::done()
{
    if (m_entity != NULL) {
        m_layer->removeEntity(m_entity);
        m_layer = NULL;
        m_entity = NULL;
        m_state = FINISHED;
        if (m_transform != NULL && m_controlTransformLifeCycle) {
            delete m_transform;
            m_transform = NULL;
        }
    }
}

void Hit::update(const double elapsedTime)
{
    switch(m_state) {
    case APPEAR:
        updateAppear(elapsedTime);
        break;
    case SHOWING:
        updateShowing(elapsedTime);
        break;
    case FINISHED:
        break;
    }
}

void Hit::updateAppear(const double elapsedTime)
{
    m_timeout -= elapsedTime;
    if (m_timeout <= 0) {
        m_state = SHOWING;
        m_timeout = m_duration;
    }
}

void Hit::updateShowing(const double elapsedTime)
{
    m_timeout -= elapsedTime;
    if (m_timeout <= 0) {
        m_state = FINISHED;
        m_layer->removeEntity(m_entity);
        m_entity = NULL;
    } else  if (m_transform)
        m_transform->updateTransform(m_entity, 1 - m_timeout / m_duration);

}
