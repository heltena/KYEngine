#pragma once

#include <KYEngine/TemplateActionFactory.h>

#include <tinyxml.h>

class SceneManager;

class AnimSceneActionFactory
    : public TemplateActionFactory
{
private:
    friend class SceneManager;
    AnimSceneActionFactory() { }
    virtual ~AnimSceneActionFactory() { }

// TemplateActionFactory implementation
public:
	Action* readFromXml(const std::string& prefix, TiXmlElement* node);
};
