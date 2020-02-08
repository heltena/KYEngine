#pragma once

#include <KYEngine/AnimMeshInfo.h>

#include <string>

class AnimMeshCollection
{
public:
    virtual ~AnimMeshCollection() { }
    virtual const std::string& defaultAnimRef() const = 0;
	virtual int animCount() const = 0;
    virtual AnimMeshInfo* animMesh(const std::string& name) = 0;
};
