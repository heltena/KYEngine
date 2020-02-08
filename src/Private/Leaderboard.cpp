#include <KYEngine/Private/Leaderboard.h>

#include <stdexcept>

Leaderboard::Leaderboard()
    : m_id("")
    , m_value(0)
{
}

Leaderboard::Leaderboard(const std::string& id, int value)
    : m_id(id)
    , m_value(value)
{
}

Leaderboard::Leaderboard(const Leaderboard& other)
    : m_id(other.m_id)
    , m_value(other.m_value)
{
}

Leaderboard::~Leaderboard()
{
}
