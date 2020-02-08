#include <KYEngine/HudMapViewItem.h>

HudMapViewItem::HudMapViewItem()
    : m_pos(0)
    , m_type(0)
    , m_direction(DIRECTION_ZERO)
{
}

HudMapViewItem::HudMapViewItem(double pos, int type, DirectionEnum direction)
    : m_pos(pos)
    , m_type(type)
    , m_direction(direction)
{
}

HudMapViewItem::HudMapViewItem(const HudMapViewItem& other)
    : m_pos(other.m_pos)
    , m_type(other.m_type)
    , m_direction(other.m_direction)
{
}

HudMapViewItem::~HudMapViewItem()
{
}
