#pragma once

#include <KYEngine/Utility/Mutex.h>
#include <KYEngine/Utility/TiXmlNodeHelper.h>

#include <set>

class Leaderboard;
class InfoManager;

class LeaderboardList
{
public:
    LeaderboardList();
    virtual ~LeaderboardList();

public:
    void updateLeaderboard(const std::string& leaderboardName, int value);

private:
    friend class InfoManager;
    void receiveLeaderboardFromGameCenter(const std::string& leaderboardName, int value);
    const std::set<Leaderboard>& leaderboards() const { return m_leaderboards; }
    void loadFromNode(TiXmlNodeHelper* userNode);
    void saveToNode(TiXmlNodeHelper* userNode);

private:
    std::set<Leaderboard> m_leaderboards;
    RecursiveMutex m_mutex;
};
