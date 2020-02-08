#pragma once

#include "StreetFighter-Hit.h"
#include "StreetFighter-HitTransform.h"
#include "RenderLayer.h"
#include "Vector4.h"

#include <list>

namespace StreetFighter
{

    class Hits
    {
    public:
        Hits();
        virtual ~Hits();
        
    public:
        void init(RenderLayer* layer, double z, const std::string& animMeshCollectionRef, const std::string& defaultAnimRef);
        void done() { removeAll(); }
        void addHit(const Vector4& pos, double duration, double delay = 0, const std::string& animRef = "", HitTransform* transform = NULL, bool controlTransformLifeCycle = true);
        void removeAll();
        void update(const double elapsedTime);
        
    private:
        RenderLayer* m_layer;
        double m_z;
        std::string m_animMeshCollectionRef;
        std::string m_defaultAnimRef;
        std::list<Hit*> m_hits;
    };
    
}