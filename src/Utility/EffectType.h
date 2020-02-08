#pragma once

#include <string>

enum EffectType
{
    EFFECT_NOTHING,
    EFFECT_LEFT,
    EFFECT_RIGHT,
    EFFECT_BOTTOM,
    EFFECT_TOP
};

const std::string effectToString(const EffectType effect) throw();
EffectType stringToEffect(const std::string& value) throw();