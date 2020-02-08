#include <KYEngine/Private/Resources/AnimMeshInfoInternal.h>
#include <KYEngine/Core.h>

AnimMeshInfoInternal::AnimMeshInfoInternal()
{
}

AnimMeshInfoInternal::AnimMeshInfoInternal(const std::string& meshRef, double fps, bool loop)
    : AnimMeshInfo(NULL, fps, loop)
    , m_meshRef(meshRef)
{
}

AnimMeshInfoInternal::AnimMeshInfoInternal(const AnimMeshInfoInternal& other)
    : AnimMeshInfo(other)
    , m_meshRef(other.m_meshRef)
{
}

AnimMeshInfoInternal::~AnimMeshInfoInternal()
{
}   

void AnimMeshInfoInternal::preload()
{
}

void AnimMeshInfoInternal::unloadFromPreloaded()
{
}

void AnimMeshInfoInternal::load()
{
    m_mesh = Core::resourceManager().mesh(m_meshRef);
}

void AnimMeshInfoInternal::unload()
{
    m_mesh = NULL;
}