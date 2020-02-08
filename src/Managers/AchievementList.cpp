#include <KYEngine/Managers/AchievementList.h>

#include <KYEngine/Private/Achievement.h>

#include <KYEngine/Utility/MutexScopeLocker.h>

#include <stdexcept>

AchievementList::AchievementList()
{
}

AchievementList::~AchievementList()
{
}

bool AchievementList::updateAchievementPercentage(const std::string& achievementName, float percentage)
{
    MutexScopeLocker msl(m_mutex);
    bool result;
    
    std::set<Achievement>::iterator found = m_achievements.find(Achievement(achievementName));
    if (found == m_achievements.end()) {
        m_achievements.insert(Achievement(achievementName, percentage));
        result = percentage >= 100;
    } else {
        Achievement achievement = *found;
        result = achievement.updatePercentage(percentage);
        
        m_achievements.erase(found);
        m_achievements.insert(achievement);
    }
    return result;
}

void AchievementList::receiveAchievementStatusFromGameCenter(const std::string& achievementName, float percentage)
{
    MutexScopeLocker msl(m_mutex);
    updateAchievementPercentage(achievementName, percentage);
}

void AchievementList::loadFromNode(TiXmlNodeHelper* userNode)
{
    MutexScopeLocker msl(m_mutex);

    TiXmlNodeHelper* node = userNode->simpleXPathAsNode("achievement-list");
    if (node == NULL)
        return;

    const std::vector<TiXmlNodeHelper*>& children = node->children();
    for (std::vector<TiXmlNodeHelper*>::const_iterator it = children.begin(); it != children.end(); it++) {
        TiXmlNodeHelper* cur = *it;
        std::string id = cur->simpleXPath("id");
        float percentage = cur->simpleXPathAsDouble("percentage");
        updateAchievementPercentage(id, percentage);
    }
}

void AchievementList::saveToNode(TiXmlNodeHelper* userNode)
{
    MutexScopeLocker msl(m_mutex);

    int index = 0;
    for(std::set<Achievement>::const_iterator it = m_achievements.begin(); it != m_achievements.end(); it++) {
        const Achievement& achievement = *it;
        std::stringstream ss;
        ss << "achievement-list/achievement[" << index++ << "]";
        userNode->setSimpleXPath(ss.str() + "/id", achievement.id());
        userNode->setSimpleXPath(ss.str() + "/percentage", achievement.percentage());
    }
}
