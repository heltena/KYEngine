#include <KYEngine/Private/Achievement.h>

#include <stdexcept>

Achievement::Achievement()
    : m_id("")
    , m_percentage(0)
{
}

Achievement::Achievement(const std::string& id, float percentage, bool earnAdvicedToUser)
    : m_id(id)
    , m_percentage(percentage)
{
    if (m_percentage > 100)
        m_percentage = 100;
}

Achievement::Achievement(const Achievement& other)
    : m_id(other.m_id)
    , m_percentage(other.m_percentage)
{
}

Achievement::~Achievement()
{
}

bool Achievement::updatePercentage(float percentage)
{
    if (percentage > 100)
        percentage = 100;
    
    if (m_percentage >= percentage)
        return false;
    else {
        m_percentage = percentage;
        return m_percentage >= 100;
    }
}
