#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

class ParticleEmitterExtension
{
public:
    virtual ~ParticleEmitterExtension() { }
    virtual Entity* entity() = 0;
    virtual ParticleEmitterExtension* clone() = 0;
    virtual void start() = 0;
    virtual void start(double timeout) = 0;
    virtual void start(const Vector4& pos) = 0;
    virtual void start(double timeout, const Vector4& pos) = 0;
    virtual void update(const double elapsedTime) = 0;
    virtual void stop() = 0;
    virtual bool isPaused() const = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual bool isFinished() const = 0;
};