#pragma once

#include <string>

class Entity;

class AnimMeshExtension
{
public:
    virtual ~AnimMeshExtension() { }
    virtual Entity* entity() = 0;
	virtual void setAnim(const std::string& animRef, double fps = 0) = 0;
    virtual const std::string animRef() const = 0;
    virtual double fps() const = 0;
    virtual bool isFinished() const = 0;
    virtual double loopDuration() const = 0;
    virtual double loopDuration(double fps) const = 0;
};