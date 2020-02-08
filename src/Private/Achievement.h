#pragma once

#include <string>

class Achievement
{
public:
    Achievement();
    Achievement(const std::string& id, float percentage = 0, bool earnAdvicedToUser = false);
    Achievement(const Achievement& other);
    virtual ~Achievement();

public:
    const std::string& id() const { return m_id; }
    float percentage() const { return m_percentage; }

public:
    bool updatePercentage(float percentage); // returns needAdvice
    
public:
    bool operator<(const Achievement& other) const { return m_id < other.m_id; }
    bool operator=(const Achievement& other) const { return m_id == other.m_id; }

private:
    const std::string m_id;
    float m_percentage;
};
