#include <KYEngine/Private/Huds/HudMapViewItemType.h>

HudMapViewItemType::HudMapViewItemType()
    : m_id(0)
    , m_leftMesh(NULL)
    , m_rightMesh(NULL)
{
}

HudMapViewItemType::HudMapViewItemType(int id, Mesh* leftMesh, Mesh* rightMesh)
    : m_id(id)
    , m_leftMesh(leftMesh)
    , m_rightMesh(rightMesh)
{
}

HudMapViewItemType::HudMapViewItemType(const HudMapViewItemType& other)
    : m_id(other.m_id)
    , m_leftMesh(other.m_leftMesh)
    , m_rightMesh(other.m_rightMesh)
{
}

HudMapViewItemType::~HudMapViewItemType()
{
}
