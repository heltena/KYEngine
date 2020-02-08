#pragma once

#include <KYEngine/HitContainer.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>
#include <string>

class Hit;
class HitTransform;

class HitContainerImpl
    : public HitContainer
{
public:
    HitContainerImpl(const std::string& name, int zorder, const std::string& animMeshCollectionRef, const std::string& defaultAnimRef);
    virtual ~HitContainerImpl();

// HitContainer
public:
    void addHit(const Vector4& pos, double duration, double delay = 0, const std::string& animRef = "", HitTransform* transform = NULL, bool controlTransformLifeCycle = true);
    void removeAllHits();

public:
    void update(const double elapsedTime);

private:
    RenderLayer* m_layer;
    std::string m_name;
    int m_zorder;
    std::string m_animMeshCollectionRef;
    std::string m_defaultAnimRef;
    
    std::list<Hit*> m_hits;
};