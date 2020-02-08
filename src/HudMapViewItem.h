#pragma once

#include <KYEngine/Utility/DirectionEnum.h>

class HudMapViewItem
{
public:
    HudMapViewItem();
    HudMapViewItem(double pos, int type, DirectionEnum direction = DIRECTION_ZERO);
    HudMapViewItem(const HudMapViewItem& other);
    virtual ~HudMapViewItem();
    
public:
    double pos() const { return m_pos; }
    int type() const { return m_type; }
    DirectionEnum direction() const { return m_direction; }
    
private:
    double m_pos;
    int m_type;
    DirectionEnum m_direction;
};