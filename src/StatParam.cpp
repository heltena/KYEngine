#include <KYEngine/StatParam.h>

StatParam::StatParam()
    : m_defaultValue(0)
    , m_currentValue(0)
{
}

StatParam::StatParam(const StatParam& other)
    : m_name(other.m_name)
    , m_description(other.m_description)
    , m_defaultValue(other.m_defaultValue)
    , m_currentValue(other.m_currentValue)
{
}

StatParam::~StatParam()
{
}
