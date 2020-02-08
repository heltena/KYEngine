#include <KYEngine/Core.h>
#include <KYEngine/Private/Hits/Hit.h>
#include <KYEngine/Private/Hits/HitContainerImpl.h>

HitContainerImpl::HitContainerImpl(const std::string& name, int zorder, const std::string& animMeshCollectionRef, const std::string& defaultAnimRef)
    : m_name(name)
    , m_zorder(zorder)
    , m_animMeshCollectionRef(animMeshCollectionRef)
    , m_defaultAnimRef(defaultAnimRef)
{

    m_layer = Core::renderManager().createLayer(m_name, m_zorder);
}

HitContainerImpl::~HitContainerImpl()
{
    Core::renderManager().removeLayer(m_name);
}

void HitContainerImpl::addHit(const Vector4& pos, double duration, double delay, const std::string& animRef, HitTransform* transform, bool controlTransformLifeCycle)
{
    Hit* hit = new Hit();
    Vector4 pos2(pos[0], pos[1], m_zorder, 1);
    hit->init(m_layer, pos2, duration, m_animMeshCollectionRef, animRef.length() ? animRef : m_defaultAnimRef, delay, transform, controlTransformLifeCycle);
    m_hits.push_back(hit);
}

void HitContainerImpl::removeAllHits()
{
    for(std::list<Hit*>::iterator it = m_hits.begin(); it != m_hits.end(); it++) {
        Hit* hit = *it;
        hit->done();
        delete hit;
    }
    m_hits.clear();
}

void HitContainerImpl::update(const double elapsedTime)
{
    std::list<Hit*>::iterator it = m_hits.begin();
    while (it != m_hits.end()) {
        Hit* hit = *it;
        hit->update(elapsedTime);
        if (hit->isFinished()) {
            std::list<Hit*>::iterator toKill = it++;
            hit->done();
            delete hit;
            m_hits.erase(toKill);
        } else
            it++;
    }
}
