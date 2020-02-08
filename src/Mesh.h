#pragma once

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Optimizations/OptimizedMeshData.h>

#include <string>

class Mesh
{
protected:
    virtual ~Mesh() { }
public:
    virtual const std::string& name() const = 0;
	virtual int frameCount() const = 0;
	virtual void draw(double hpercent, int frame = 0) = 0;
	virtual const Box& boundingBox() const = 0;
    virtual void addMeshDataTo(OptimizedMeshData& data) = 0;
    virtual void* userData() = 0;
};