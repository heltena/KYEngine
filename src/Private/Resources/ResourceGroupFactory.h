#pragma once

#include <tinyxml.h>

#include <KYEngine/TemplateResourceFactory.h>

class PlayingHudFactoryListener;
class ResourceGroupFactoryListener;
class ResourceManager;

class ResourceGroupFactory
    : public TemplateResourceFactory
{
private:
    friend class ResourceManager;
    ResourceGroupFactory() { }
    virtual ~ResourceGroupFactory() { }

// TemplateResourceFactory implementation
public:
    virtual void readFromXml(const std::string& prefix, TiXmlElement* node, ResourceGroupFactoryListener* listener);
    virtual void readFromXml(const std::string& prefix, TiXmlElement* node, PlayingHudFactoryListener* listener);
};