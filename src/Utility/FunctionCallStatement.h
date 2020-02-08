#pragma once

#include <string>
#include <vector>

class FunctionCallStatement
{
public:
    FunctionCallStatement();
    virtual ~FunctionCallStatement();
    
public:
    void init(std::string statement);
    
public:
    bool hasErrors() const { return m_hasErrors; }
    const std::string& functionName() const { return m_functionName; }
    const int paramSize() const { return m_params.size(); }
    bool matchWith(const std::string& functionName, int paramSize) const { return m_functionName == functionName && paramSize == m_params.size(); }
    const std::string& param(int index) const { return m_params[index]; }
    bool paramAsBool(int index) const;
    double paramAsDouble(int index) const;
    int paramAsInt(int index) const;
    
    void debug();
    
private:
    bool m_hasErrors;
    std::string m_functionName;
    std::vector<std::string> m_params;
};