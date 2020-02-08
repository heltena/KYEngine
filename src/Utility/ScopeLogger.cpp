#include <KYEngine/Utility/ScopeLogger.h>

#include <iostream>

int ScopeLogger::m_levels = 0;

ScopeLogger::ScopeLogger(const std::string& prefix)
    : m_prefix(prefix)
{
    m_levels++;
    std::cout << "ScopeLogger: " << m_prefix << " enter... " << m_levels << std::endl;
    if (m_levels > 1)
        std::cout << "  WARNING" << std::endl;
}

ScopeLogger::~ScopeLogger()
{
    std::cout << "ScopeLogger: " << m_prefix << " ... leave" << m_levels << std::endl;
    m_levels--;
}