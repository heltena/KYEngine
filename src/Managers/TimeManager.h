#pragma once

#include <map>
#include <string>

class Core;
class TimeManager
{
private:
    friend class Core;
    TimeManager();
    virtual ~TimeManager(); 
    
public:
    int createTimer(const std::string& name);
    int timer(const std::string& name);
    void destroyTimer(const std::string& name);
    double timerValue(int timerId);

private:
    void update(double elapsedTime);

private:
    int m_nextTimerId;
    std::map<std::string, int> m_timerIds;
    std::map<int, double> m_timerValues;
};