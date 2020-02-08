#pragma once

#include <KYEngine/Utility/Mutex.h>
#include <KYEngine/Utility/TiXmlNodeHelper.h>

#include <set>

class Achievement;
class InfoManager;

class AchievementList
{
public:
    AchievementList();
    virtual ~AchievementList();

public:
    bool updateAchievementPercentage(const std::string& achievementName, float percentage = 100.0f);

private:
    friend class InfoManager;
    void receiveAchievementStatusFromGameCenter(const std::string& achievementName, float percentage);
    const std::set<Achievement>& achievements() const { return m_achievements; }
    void loadFromNode(TiXmlNodeHelper* userNode);
    void saveToNode(TiXmlNodeHelper* userNode);

private:
    std::set<Achievement> m_achievements;
    RecursiveMutex m_mutex;
};
