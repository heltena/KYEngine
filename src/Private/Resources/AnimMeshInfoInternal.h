#pragma once

#include <KYEngine/AnimMeshInfo.h>

#include <string>

class AnimMeshInfoInternal
    : public AnimMeshInfo
{
public:
    AnimMeshInfoInternal();
    AnimMeshInfoInternal(const std::string& meshRef, double fps, bool loop);
    AnimMeshInfoInternal(const AnimMeshInfoInternal& other);
    virtual ~AnimMeshInfoInternal();
    
public:
    void preload();
    void unloadFromPreloaded();
    void load();
    void unload();
    
private:
    std::string m_meshRef;
};