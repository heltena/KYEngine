#pragma once

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class AnimMeshExtension;
class ParticleEmitterExtension;
class RenderLayer;
class TextLayerExtension;

class Entity
{
public:
    virtual ~Entity() { }
    virtual Entity* cloneEntity() = 0;
    virtual ParticleEmitterExtension* particleEmitterInterface() = 0;
    virtual TextLayerExtension* textLayerInterface() = 0;
    virtual AnimMeshExtension* animMeshInterface() = 0;
    virtual const std::string& name() const = 0;
    virtual void setLayer(RenderLayer* layer) = 0;
    virtual const Vector4& pos() const = 0;
	virtual void setPos(const Vector4& pos) = 0;
    virtual double hpercent() const = 0;
    virtual void setHpercent(double hpercent) = 0;
	virtual const Box& screenBounds() const = 0;
	virtual Vector4& color() = 0;
	virtual void setColor(const Vector4& color) = 0;
    virtual double angle() const = 0;
    virtual void setAngle(double angle) = 0;
    virtual Vector4& scale() = 0;
    virtual void setScale(const Vector4& scale) = 0;
    virtual double alpha() const = 0;
    virtual void setAlpha(double alpha) = 0;
    virtual bool useBlending() const = 0;
    virtual void setUseBlending(bool useBlending) = 0;
	virtual void setAnim(const std::string& animRef, double fps = 0) = 0;
	virtual void update(const double elapsedTime) = 0;
	virtual void drawOpaque() = 0;
    virtual void drawSemiTransparent() = 0;
    virtual void* userData() = 0;
};