#pragma once

#include <KYEngine/Mesh.h>

class AnimMeshInfo
{
public:
    AnimMeshInfo();
    AnimMeshInfo(Mesh* mesh, double fps, bool loop);
    AnimMeshInfo(const AnimMeshInfo& other);
    virtual ~AnimMeshInfo();
    
public:
    Mesh* mesh() { return m_mesh; }
    double fps() const { return m_fps; }
    bool loop() const { return m_loop; }
    
protected:
    Mesh* m_mesh;
    double m_fps;
    bool m_loop;
};