#include <KYEngine/AnimMeshInfo.h>

AnimMeshInfo::AnimMeshInfo()
    : m_mesh(NULL)
    , m_fps(0)
    , m_loop(false)
{    
}

AnimMeshInfo::AnimMeshInfo(Mesh* mesh, double fps, bool loop)
    : m_mesh(mesh)
    , m_fps(fps)
    , m_loop(loop)
{
}

AnimMeshInfo::AnimMeshInfo(const AnimMeshInfo& other)
    : m_mesh(other.m_mesh)
    , m_fps(other.m_fps)
    , m_loop(other.m_loop)
{
}

AnimMeshInfo::~AnimMeshInfo()
{
}
