#pragma once

#include <KYEngine/TemplateResourceFactory.h>

#include <list>
#include <map>
#include <string>

class AnimMeshCollection;
class Atrezzo;
class Core;
class Entity;
class Font;
class Mesh;
class Music;
class PlayingHud;
class RawData;
class ResourceGroup;
class ResourceGroupFactory;
class Scene;
class SoundBuffer;
class Texture;
class TiXmlNode;

class ResourceManager
{
private:
	friend class Core;
	ResourceManager();
	virtual ~ResourceManager();
	
public:
	void registerLibrary(const std::string& prefix, TemplateResourceFactory* factory);
	void loadResources(const std::string& filename);

private:
    void loadResourcesButImportFiles(const std::string& filename, std::list<std::string>& importFiles);
    
public:
	std::string prefixOfNode(TiXmlNode* node);
    TemplateResourceFactory* factory(const std::string& prefix);
    TemplateResourceFactory* factoryOfNode(TiXmlNode* node) { return factory(prefixOfNode(node)); }
    
    AnimMeshCollection* animMeshCollection(const std::string& name);
    Atrezzo* atrezzo(const std::string& name);
    Entity* entity(const std::string& name);
	Font* font(const std::string& name);
	Mesh* mesh(const std::string& name);
	Music* music(const std::string& name);
    PlayingHud* playingHud(const std::string& name);
    RawData* rawData(const std::string& name);
	SoundBuffer* soundBuffer(const std::string& name);
	Texture* texture(const std::string& name);

    void preloadResourceGroups(const std::list<std::string>& resourceGroupNames);
	void loadResourceGroups(const std::list<std::string>& resourceGroupNames);
	void unloadResourceGroups(const std::list<std::string>& resourceGroupNames);
    void unloadAllPreloadedResourceGroups();

    const std::list<std::string> groupDependences(const std::string& groupName);
    const std::list<std::string> deepGroupDependences(const std::string& groupName);

    void loadGlobalResources();

    std::string debugInfo() const;
    
private:
    std::map<std::string, TemplateResourceFactory*> m_factories;
    ResourceGroupFactory* m_primaryResourceGroupFactory;
	std::map<std::string, ResourceGroup*> m_resourceGroups;
};
