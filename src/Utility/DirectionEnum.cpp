#include <KYEngine/Utility/DirectionEnum.h>

#include <stdexcept>

const std::string directionToString(const DirectionEnum direction) throw()
{
    switch(direction) {
        case DIRECTION_ZERO:
            return "";
        case DIRECTION_LEFT:
            return "left";
        case DIRECTION_RIGHT:
            return "right";
        case DIRECTION_UP:
            return "up";
        case DIRECTION_DOWN:
            return "down";
        default:
            throw std::runtime_error("directionToString: direction error");
    }
}

DirectionEnum stringToDirection(const std::string& value) throw()
{
    if (value == "")
        return DIRECTION_ZERO;
    else if (value == "left")
        return DIRECTION_LEFT;
    else if (value == "right")
        return DIRECTION_RIGHT;
    else if (value == "up")
        return DIRECTION_UP;
    else if (value == "down")
        return DIRECTION_DOWN;
    else
        throw std::runtime_error("stringToDirection: string error");
}