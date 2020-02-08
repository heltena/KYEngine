#pragma once

#include <string>

enum DirectionEnum {
    DIRECTION_ZERO,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN
};

const std::string directionToString(const DirectionEnum direction) throw();
DirectionEnum stringToDirection(const std::string& value) throw();