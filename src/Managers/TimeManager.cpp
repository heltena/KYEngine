#include <KYEngine/Managers/TimeManager.h>

#include <iostream>
#include <stdexcept>

TimeManager::TimeManager()
    : m_nextTimerId(0)
{
}

TimeManager::~TimeManager()
{
}

int TimeManager::createTimer(const std::string& name)
{
#ifdef DEBUG
    std::map<std::string, int>::iterator it = m_timerIds.find(name);
    if (it != m_timerIds.end())
        throw std::runtime_error("TimeManager::createTimer time just exists");
#endif
    
    int timerId = m_nextTimerId++;
    m_timerIds[name] = timerId;
    m_timerValues[timerId] = 0;
    return timerId;
}

int TimeManager::timer(const std::string& name)
{
    std::map<std::string, int>::iterator it = m_timerIds.find(name);
    if (it == m_timerIds.end())
        throw std::runtime_error("TimeManager::createTimer time doesn't exist");
    return it->second;
}

void TimeManager::destroyTimer(const std::string& name)
{
    std::map<std::string, int>::iterator it = m_timerIds.find(name);
    if (it == m_timerIds.end())
        throw std::runtime_error("TimeManager::createTimer time doesn't exist");
    int timerId = it->second;
    m_timerIds.erase(it);
    
    m_timerValues.erase(timerId);
}

double TimeManager::timerValue(int timerId)
{
    return m_timerValues[timerId];
}

void TimeManager::update(double elapsedTime)
{
    for(std::map<int, double>::iterator it = m_timerValues.begin(); it != m_timerValues.end(); it++)
        it->second += elapsedTime;
}