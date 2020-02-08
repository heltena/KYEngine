#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <string>

class HitTransform;

class HitContainer
{
public:
    virtual ~HitContainer() { }
    
    virtual void addHit(const Vector4& pos, double duration, double delay = 0, const std::string& animRef = "", HitTransform* transform = NULL, bool controlTransformLifeCycle = true) = 0;
    virtual void removeAllHits() = 0;
};
