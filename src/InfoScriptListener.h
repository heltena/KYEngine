#pragma once

#include <string>

class InfoScriptListener
{
public:
    virtual const std::string& infoParam(const std::string& name) = 0;
    virtual void infoScriptSetParam(const std::string& name, const std::string& value) = 0;
};

