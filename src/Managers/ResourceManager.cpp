#include <CoreFoundation/CoreFoundation.h>

#include <KYEngine/Core.h>
#include <KYEngine/Private/Natives/RawFileReader.h>
#include <KYEngine/Private/Resources/ResourceGroupFactory.h>
#include <KYEngine/Private/Resources/ResourceGroup.h>
#include <KYEngine/Managers/ResourceManager.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <tinyxml.h>

#include <iostream>
#include <stdexcept>

ResourceManager::ResourceManager()
{
    m_primaryResourceGroupFactory = new ResourceGroupFactory();
    registerLibrary("", m_primaryResourceGroupFactory);
}

ResourceManager::~ResourceManager()
{
    delete m_primaryResourceGroupFactory;
}

void ResourceManager::registerLibrary(const std::string& prefix, TemplateResourceFactory* factory)
{
    m_factories[prefix] = factory;
}

void ResourceManager::loadResources(const std::string& filename)
{
    std::list<std::string> importFiles;
    
    loadResourcesButImportFiles(filename, importFiles);
    
    for(std::list<std::string>::const_iterator it = importFiles.begin(); it != importFiles.end(); it++)
                loadResources(*it);
}

void ResourceManager::loadResourcesButImportFiles(const std::string& filename, std::list<std::string>& importFiles)
{
    RawFileReader reader(filename, "xml");
    
	TiXmlDocument doc(reader.resFilename().c_str());
	doc.Parse(reader.content());
	
	TiXmlHandle hDoc(&doc);
	
	// Get Root Handle
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse resource file: " + reader.resFilename());
	TiXmlHandle hRoot = TiXmlHandle(pElem);
	
	// Global info
	{
		TiXmlElement* element = hRoot.ToElement();
		std::string rootNode = element->Value();
		if (rootNode != "resources")
			throw std::runtime_error("file '" + reader.resFilename() + "' doesn't contain 'resources' root node");
	}
	
    // Read import-file
    {
        TiXmlElement* pElement = hRoot.FirstChild("import-file").Element();
        while(pElement) {
            importFiles.push_back(pElement->Attribute("filename"));
            pElement = pElement->NextSiblingElement("import-file");
        }
    }
    
	// Read resource-groups
	{
		TiXmlElement* pElement = hRoot.FirstChild("resource-group").Element();
		while (pElement) {
            std::string name = pElement->Attribute("name");
            bool isGlobal = TiXmlHelper::readBool(pElement, "is-global", false, false);
            
            ResourceGroup* newGroup = new ResourceGroup();
            newGroup->setName(name);
            newGroup->setIsGlobal(isGlobal);
            
            TiXmlElement* node = pElement->FirstChildElement();
            while (node) {
                std::string prefix = prefixOfNode(node);
                factory(prefix)->readFromXml(prefix, node, newGroup);

                m_resourceGroups[name] = newGroup;
                node = node->NextSiblingElement();
            }
    
            pElement = pElement->NextSiblingElement("resource-group");
		}
	}
}

std::string ResourceManager::prefixOfNode(TiXmlNode* node)
{
    std::string prefix;
    const std::string& nodeValue = node->Value();
    size_t dots = nodeValue.find_first_of(':');
    if (dots == std::string::npos)
        prefix = "";
    else
        prefix = nodeValue.substr(0, dots);
    return prefix;
}

TemplateResourceFactory* ResourceManager::factory(const std::string& prefix)
{
    std::map<std::string, TemplateResourceFactory*>::iterator it = m_factories.find(prefix);
    if (it == m_factories.end())
        throw std::runtime_error("ResourceManager: factory with prefix '" + prefix + "' not registered");
    return it->second;
    
}

AnimMeshCollection* ResourceManager::animMeshCollection(std::string const &name)
{
    AnimMeshCollection* result = NULL;
    std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
    while (result == NULL && it != m_resourceGroups.end()) {
        if (it->second->isLoaded())
            result = it->second->animMeshCollection(name);
        it++;
    }
#ifdef DEBUG
    if (!result)
        throw std::runtime_error("animMeshCollection not found " + name);
#endif
    return result;
}

Atrezzo* ResourceManager::atrezzo(std::string const &name)
{
    Atrezzo* result = NULL;
    std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
    while (result == NULL && it != m_resourceGroups.end()) {
        if (it->second->isLoaded())
            result = it->second->atrezzo(name);
        it++;
    }
#ifdef DEBUG
    if (!result)
        throw std::runtime_error("atrezzo not found " + name);
#endif
    return result;
}

Entity* ResourceManager::entity(const std::string& name)
{
	Entity* result = NULL;
	std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
	while (result == NULL && it != m_resourceGroups.end()) {
		if (it->second->isLoaded())
			result = it->second->entity(name);
		it++;
	}
#ifdef DEBUG
	if (!result)
		throw std::runtime_error("entity not found " + name);
#endif
	return result;
}

Font* ResourceManager::font(const std::string& name)
{
	Font* result = NULL;
	std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
	while (result == NULL && it != m_resourceGroups.end()) {
		if (it->second->isLoaded())
			result = it->second->font(name);
		it++;
	}
#ifdef DEBUG 
	if (!result)
		throw std::runtime_error("font not found " + name);
#endif
	return result;
}

Mesh* ResourceManager::mesh(const std::string& name)
{
    Mesh* result = NULL;
	std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
	while (result == NULL && it != m_resourceGroups.end()) {
		if (it->second->isLoaded())
			result = it->second->mesh(name);
		it++;
	}
#ifdef DEBUG
	if (!result)
		throw std::runtime_error("mesh not found " + name);
#endif
	return result;
}

Music* ResourceManager::music(const std::string& name)
{
	Music* result = NULL;
	std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
	while (result == NULL && it != m_resourceGroups.end()) {
		if (it->second->isLoaded())
			result = it->second->music(name);
		it++;
	}
#ifdef DEBUG
	if (!result)
		throw std::runtime_error("music not found " + name);
#endif
	return result;
}

PlayingHud* ResourceManager::playingHud(const std::string& name)
{
    PlayingHud* result = NULL;
    std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
    while (result == NULL && it != m_resourceGroups.end()) {
        if (it->second->isLoaded())
            result = it->second->playingHud(name);
        it++;
    }
#ifdef DEBUG
    if (!result)
        throw std::runtime_error("playingHud not found " + name);
#endif
    return result;
}

RawData* ResourceManager::rawData(const std::string& name)
{
    RawData* result = NULL;
    std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
    while (result == NULL && it != m_resourceGroups.end()) {
        if (it->second->isLoaded())
            result = it->second->rawData(name);
        it++;
    }
#ifdef DEBUG
    if (!result)
        throw std::runtime_error("rawData not found '" + name + "'");
#endif
    return result;
}

SoundBuffer* ResourceManager::soundBuffer(const std::string& name)
{
	SoundBuffer* result = NULL;
	std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
	while (result == NULL && it != m_resourceGroups.end()) {
		if (it->second->isLoaded())
			result = it->second->soundBuffer(name);
		it++;
	}
#ifdef DEBUG
	if (!result)
		throw std::runtime_error("soundBuffer not found " + name);
#endif
	return result;
}

Texture* ResourceManager::texture(const std::string& name)
{
	Texture* result = NULL;
	std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin();
	while (result == NULL && it != m_resourceGroups.end()) {
		if (it->second->isLoaded())
			result = it->second->texture(name);
		it++;
	}
#ifdef DEBUG
	if (!result)
		throw std::runtime_error("texture not found " + name);
#endif
	return result;
}

void ResourceManager::preloadResourceGroups(const std::list<std::string>& resourceGroupNames)
{
	std::list<std::string>::const_iterator it = resourceGroupNames.begin();
	while (it != resourceGroupNames.end()) {
		ResourceGroup* group = m_resourceGroups[*it];
#ifdef DEBUG
        if (group == NULL)
            throw std::runtime_error("resource group not found (loading) " + *it);
#endif
		group->preload();
		it++;
	}
}

void ResourceManager::loadResourceGroups(const std::list<std::string>& resourceGroupNames)
{
	std::list<std::string>::const_iterator it = resourceGroupNames.begin();
	while (it != resourceGroupNames.end()) {
        ResourceGroup* group = m_resourceGroups[*it];
#ifdef DEBUG
        if (group == NULL)
            throw std::runtime_error("resource group not found (loading) " + *it);
#endif
		group->load();
		it++;
	}
}

void ResourceManager::unloadResourceGroups(const std::list<std::string>& resourceGroupNames)
{
	std::list<std::string>::const_iterator it = resourceGroupNames.begin();
	while (it != resourceGroupNames.end()) {
		ResourceGroup* group = m_resourceGroups[*it];
#ifdef DEBUG
        if (group == NULL)
            throw std::runtime_error("resource group not found (unloading) " + *it);
#endif
		group->unload();
		it++;
	}
}

void ResourceManager::unloadAllPreloadedResourceGroups()
{
    for(std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin(); it != m_resourceGroups.end(); it++) {
        if (it->second->isPreloaded())
            it->second->unloadFromPreloaded();
    }
}

const std::list<std::string> ResourceManager::groupDependences(const std::string& groupName)
{
    std::map<std::string, ResourceGroup*>::iterator found = m_resourceGroups.find(groupName);
    if (found == m_resourceGroups.end())
        return std::list<std::string>();
    else
        return found->second->groupDependences();
}

const std::list<std::string> ResourceManager::deepGroupDependences(const std::string& groupName)
{
    std::list<std::string> result;

    if (m_resourceGroups.size() == 0) {
        result.push_back(groupName);
        return result;
    }
    
    const std::list<std::string> children = Core::resourceManager().groupDependences(groupName);
    for(std::list<std::string>::const_iterator it = children.begin(); it != children.end(); it++) {
        std::list<std::string> childrenDeep = deepGroupDependences(*it);
        for(std::list<std::string>::const_iterator it2 = childrenDeep.begin(); it2 != childrenDeep.end(); it2++) {
            if (std::find(result.begin(), result.end(), *it2) == result.end())
                result.push_back(*it2);
        }
    }
    if (std::find(result.begin(), result.end(), groupName) != result.end())
        throw std::runtime_error("cycle in resource dependences");
    result.push_back(groupName);
    return result;
}

void ResourceManager::loadGlobalResources()
{
    for(std::map<std::string, ResourceGroup*>::iterator it = m_resourceGroups.begin(); it != m_resourceGroups.end(); it++) {
        if (it->second->isGlobal() && ! it->second->isLoaded())
            it->second->load();
    }
}

std::string ResourceManager::debugInfo() const
{
    std::stringstream ss;
    ss << "ResourceManager: ";
    for(std::map<std::string, ResourceGroup*>::const_iterator it = m_resourceGroups.begin(); it != m_resourceGroups.end(); it++)
        ss << it->second->debugInfo() << ", ";
    return ss.str();
}
