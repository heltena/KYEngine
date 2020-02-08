#pragma once

#include <KYEngine/Mesh.h>

class HudMapViewItemType
{
public:
    HudMapViewItemType();
    HudMapViewItemType(int id, Mesh* leftMesh, Mesh* rightMesh);
    HudMapViewItemType(const HudMapViewItemType& other);
    virtual ~HudMapViewItemType();
    
public:
    int id() const { return m_id; }
    Mesh* leftMesh() const { return m_leftMesh; }
    Mesh* rightMesh() const { return m_rightMesh; }
    
private:
    int m_id;
    Mesh* m_leftMesh;
    Mesh* m_rightMesh;
};