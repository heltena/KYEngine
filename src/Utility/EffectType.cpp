#include <KYEngine/Utility/EffectType.h>

#include <stdexcept>

const std::string effectToString(const EffectType effect) throw()
{
    switch(effect) {
    case EFFECT_NOTHING:
        return "nothing";
    case EFFECT_LEFT:
        return "left";
    case EFFECT_RIGHT:
        return "right";
    case EFFECT_BOTTOM:
        return "bottom";
    case EFFECT_TOP:
        return "top";
    default:
        throw std::runtime_error("effectToString: effect error");
    }
}

EffectType stringToEffect(const std::string& value) throw()
{
    if (value == "nothing")
        return EFFECT_NOTHING;
    else if (value == "left")
        return EFFECT_LEFT;
    else if (value == "right")
        return EFFECT_RIGHT;
    else if (value == "bottom")
        return EFFECT_BOTTOM;
    else if (value == "top")
        return EFFECT_TOP;
    else
        throw std::runtime_error("stringToEffect: string error");
}