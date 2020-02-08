#include <KYEngine/PopupInfo.h>

#include <iostream>

PopupInfo::PopupInfo()
    : m_borderWidth(0)
    , m_borderHeight(0)
    , m_appearDuration(1)
    , m_appearAccelMagnitude(1)
    , m_disappearDuration(1)
    , m_disappearAccelMagnitude(1)
    , m_useBackground(false)
{
}

PopupInfo::PopupInfo(const PopupInfo& other)
    : m_borderWidth(other.m_borderWidth)
    , m_borderHeight(other.m_borderHeight)
    , m_backgroundEntityRef(other.m_backgroundEntityRef)
    , m_fontRef(other.m_fontRef)
    , m_pos(other.m_pos)
    , m_appearDuration(other.m_appearDuration)
    , m_appearAccelMagnitude(other.m_appearAccelMagnitude)
    , m_disappearDuration(other.m_disappearDuration)
    , m_disappearAccelMagnitude(other.m_disappearAccelMagnitude)
    , m_color(other.m_color)
    , m_useBackground(other.m_useBackground)
{
}

PopupInfo::~PopupInfo()
{
}
