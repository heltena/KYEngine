#pragma once

class Entity;

class HitTransform
{
public:
    virtual ~HitTransform() { }
    virtual void updateTransform(Entity* entity, double percent) = 0;
};