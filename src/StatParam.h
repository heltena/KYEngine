#pragma once

#include <string>

class StatParam
{
public:
    StatParam();
    StatParam(const StatParam& other);
    virtual ~StatParam();

public:
    const std::string& name() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
    const std::string& description() const { return m_description; }
    void setDescription(const std::string& description) { m_description = description; }
    float defaultValue() const { return m_defaultValue; }
    void setDefaultValue(float defaultValue) { m_defaultValue = defaultValue; }
    float currentValue() const { return m_currentValue; }
    void setCurrentValue(float currentValue) { m_currentValue = currentValue; }
    void incrCurrentValue(float incr) { m_currentValue += incr; }
    bool isLevelStat() const { return m_isLevelStat; }
    void setIsLevelStat(bool isLevelStat) { m_isLevelStat = isLevelStat; }
    
private:
    std::string m_name;
    std::string m_description;
    float m_defaultValue;
    float m_currentValue;
    bool m_isLevelStat;
};