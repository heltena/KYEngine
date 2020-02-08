#pragma once

#include <KYEngine/Utility/Vector4.h>

class PlayingHudListener
{
public:
	virtual void hudButtonPressed(const Vector4& direction, int id) = 0;
    virtual void hudButtonReleased(const Vector4& direction, int id) = 0;
};