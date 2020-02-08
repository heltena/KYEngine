#pragma once

#include <KYEngine/InfoScriptListener.h>
#include <KYEngine/Utility/FunctionCallStatement.h>

class TemplateScriptFactory
{
public:
    virtual bool canExecuteScript(const FunctionCallStatement& statement, InfoScriptListener* listener) = 0;
    virtual const std::string executeScript(const FunctionCallStatement& statement, InfoScriptListener* listener) = 0;
};