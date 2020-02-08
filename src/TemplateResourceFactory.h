#pragma once

#include <tinyxml.h>

#include <string>

class PlayingHudFactoryListener;
class ResourceGroupFactoryListener;

class TemplateResourceFactory
{
public:
    virtual void readFromXml(const std::string& prefix, TiXmlElement* node, ResourceGroupFactoryListener* listener) = 0;
    virtual void readFromXml(const std::string& prefix, TiXmlElement* node, PlayingHudFactoryListener* listener) = 0;
};

