#pragma once

#include <tinyxml.h>

#include <string>

class Action;

class TemplateActionFactory
{
public:
    virtual Action* readFromXml(const std::string& prefix, TiXmlElement* node) = 0;
};