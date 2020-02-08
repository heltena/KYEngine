#pragma once

#include <string>

class Leaderboard
{
public:
    Leaderboard();
    Leaderboard(const std::string& id, int value = 0);
    Leaderboard(const Leaderboard& other);
    virtual ~Leaderboard();

public:
    const std::string& id() const { return m_id; }
    int value() const { return m_value; }

public:
    void setValue(int value) { m_value = value; }
    
public:
    bool operator<(const Leaderboard& other) const { return m_id < other.m_id; }
    bool operator=(const Leaderboard& other) const { return m_id == other.m_id; }

private:
    const std::string m_id;
    int m_value;
};
