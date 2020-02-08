#pragma once

namespace StreetFighter
{

    class HitTransform
    {
    public:
        virtual ~HitTransform() { }
        virtual void updateTransform(Entity* entity, double percent) = 0;
    };
    
}