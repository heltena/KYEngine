#pragma once

#include <string>

class ScopeLogger
{
public:
    ScopeLogger(const std::string& prefix);
    virtual ~ScopeLogger();
    
private:
    const std::string m_prefix;
    static int m_levels;
};