#pragma once

#include <KYEngine/Utility/Vector4.h>

class Entity;

class Atrezzo
{
public:
    virtual ~Atrezzo() { }
    virtual Entity* asEntity() = 0;
    virtual void setCameraPos(const Vector4& cameraPos) = 0;
    virtual const Vector4& cameraPos() const = 0;
    virtual Vector4 atrezzoToScreen(const Vector4& atrezzoPos, double extraInfo = 0) = 0;
    virtual void update(const double elapsedTime) = 0;
	virtual void drawOpaque() = 0;
    virtual void drawSemiTransparent() = 0;
};
