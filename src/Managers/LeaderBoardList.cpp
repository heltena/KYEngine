#include <KYEngine/Managers/LeaderboardList.h>

#include <KYEngine/Private/Leaderboard.h>

#include <KYEngine/Utility/MutexScopeLocker.h>

#include <stdexcept>

LeaderboardList::LeaderboardList()
{
}

LeaderboardList::~LeaderboardList()
{
}

void LeaderboardList::updateLeaderboard(const std::string& leaderboardName, int value)
{
    MutexScopeLocker msl(m_mutex);
    
    std::set<Leaderboard>::iterator found = m_leaderboards.find(Leaderboard(leaderboardName));
    if (found == m_leaderboards.end()) {
        m_leaderboards.insert(Leaderboard(leaderboardName, value));
    } else {
        Leaderboard leaderboard = *found;
        leaderboard.setValue(value);
        
        m_leaderboards.erase(found);
        m_leaderboards.insert(leaderboard);
    }
}

void LeaderboardList::receiveLeaderboardFromGameCenter(const std::string& leaderboardName, int value)
{
    MutexScopeLocker msl(m_mutex);
    updateLeaderboard(leaderboardName, value);
}

void LeaderboardList::loadFromNode(TiXmlNodeHelper* userNode)
{
    MutexScopeLocker msl(m_mutex);

    TiXmlNodeHelper* node = userNode->simpleXPathAsNode("leaderboard-list");
    if (node == NULL)
        return;

    const std::vector<TiXmlNodeHelper*>& children = node->children();
    for (std::vector<TiXmlNodeHelper*>::const_iterator it = children.begin(); it != children.end(); it++) {
        TiXmlNodeHelper* cur = *it;
        std::string id = cur->simpleXPath("id");
        int value = cur->simpleXPathAsInt("value");
        updateLeaderboard(id, value);
    }
}

void LeaderboardList::saveToNode(TiXmlNodeHelper* userNode)
{
    MutexScopeLocker msl(m_mutex);

    int index = 0;
    for(std::set<Leaderboard>::const_iterator it = m_leaderboards.begin(); it != m_leaderboards.end(); it++) {
        const Leaderboard& leaderboard = *it;
        std::stringstream ss;
        ss << "leaderboard-list/leaderboard[" << index++ << "]";
        userNode->setSimpleXPath(ss.str() + "/id", leaderboard.id());
        userNode->setSimpleXPath(ss.str() + "/value", leaderboard.value());
    }
}
