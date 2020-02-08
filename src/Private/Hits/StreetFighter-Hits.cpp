#include "StreetFighter-Hits.h"

using namespace StreetFighter;

Hits::Hits()
{
}

Hits::~Hits()
{
}

void Hits::init(RenderLayer* layer, double z, const std::string& animMeshCollectionRef, const std::string& defaultAnimRef)
{
    m_layer = layer;
    m_z = z;
    m_animMeshCollectionRef = animMeshCollectionRef;
    m_defaultAnimRef = defaultAnimRef;
    removeAll();
}

void Hits::addHit(const Vector4& pos, double duration, double delay, const std::string& animRef, HitTransform* transform, bool controlTransformLifeCycle)
{
    Hit* hit = new Hit();
    Vector4 pos2(pos[0], pos[1], m_z, 1);
    hit->init(m_layer, pos2, duration, m_animMeshCollectionRef, animRef.length() ? animRef : m_defaultAnimRef, delay, transform, controlTransformLifeCycle);
    m_hits.push_back(hit);
}

void Hits::removeAll()
{
    for(std::list<Hit*>::iterator it = m_hits.begin(); it != m_hits.end(); it++) {
        Hit* hit = *it;
        hit->done();
        delete hit;
    }
    m_hits.clear();
}

void Hits::update(const double elapsedTime)
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

