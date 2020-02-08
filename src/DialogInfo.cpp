#include <KYEngine/DialogInfo.h>

#include <iostream>

DialogInfo::DialogInfo()
    : m_borderWidth(0)
    , m_borderHeight(0)
    , m_z(0)
    , m_appearingCelerity(1)
    , m_disappearingCelerity(1)
{
}

DialogInfo::DialogInfo(const DialogInfo& other)
    : m_borderWidth(other.m_borderWidth)
    , m_borderHeight(other.m_borderHeight)
    , m_backgroundEntityRef(other.m_backgroundEntityRef)
    , m_fontRef(other.m_fontRef)
    , m_z(other.m_z)
    , m_appearingCelerity(other.m_appearingCelerity)
    , m_disappearingCelerity(other.m_disappearingCelerity)
    , m_color(other.m_color)
{
}

DialogInfo::~DialogInfo()
{
}

const Vector4& DialogInfo::color(const std::string& index) const
{
    std::map<std::string, Vector4>::const_iterator found = m_color.find(index);
    if (found == m_color.end())
        return Vector4::WHITE;
    else
        return found->second;
}

void DialogInfo::addColor(const std::string& index, const Vector4& value)
{
    m_color[index] = value;
}