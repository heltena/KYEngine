#pragma once

#include <KYEngine/Utility/Box.h>

class Core;

class Platform
{
private:
    friend class Core;
    Platform();
    Platform(const Platform& other);
    virtual ~Platform();

public:
    const Box& resolution() const { return m_resolution; }
    const std::string& suffix() const { return m_suffix; }
    
private:
    void setResolution(const Box& resolution) { m_resolution = resolution; }
    void setSuffix(const std::string& suffix) { m_suffix = suffix; }
    
private:
    Box m_resolution;
    std::string m_suffix;
};
