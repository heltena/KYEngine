#include <CoreFoundation/CoreFoundation.h>

#include <KYEngine/Private/AnimSceneActions/AnimSceneActionFactory.h>
#include <KYEngine/Private/AnimSceneImpl.h>
#include <KYEngine/Core.h>
#include <KYEngine/Private/Natives/RawFileReader.h>
#include <KYEngine/Scene.h>
#include <KYEngine/Managers/SceneManager.h>

#include <iterator>
#include <iostream>
#include <list>
#include <stdexcept>

SceneManager::SceneManager()
	: m_currentScene(NULL)
	, m_state(NOTHING)
{
    m_primarySceneFactory = new AnimSceneActionFactory();
    registerLibrary("", m_primarySceneFactory);
}

SceneManager::~SceneManager()
{
    delete m_primarySceneFactory;
}

void SceneManager::registerLibrary(const std::string& prefix, TemplateActionFactory* factory)
{
    m_factories[prefix] = factory;
}

void SceneManager::registerAnimScenes(const std::string& filename)
{
    RawFileReader reader(filename, "xml");
	
	TiXmlDocument doc(reader.resFilename().c_str());
	doc.Parse(reader.content());
	
	TiXmlHandle hDoc(&doc);
	
	// Get Root Handle
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse anim-scene file: " + reader.resFilename());
	TiXmlHandle hRoot = TiXmlHandle(pElem);
	
    // Read import-file
    {
        TiXmlElement* pElement = hRoot.FirstChild("register-scene").Element();
        while(pElement) {
            const std::string& filename =pElement->Attribute("filename");
            registerScene(filename);
            pElement = pElement->NextSiblingElement("register-scene");
        }
    }
}

void SceneManager::registerScene(Scene* scene)
{
#ifdef DEBUG
    std::map<std::string, Scene*>::iterator found = m_scenes.find(scene->name());
    if (found != m_scenes.end())
        throw std::runtime_error("SceneManager: scene exists: " + scene->name());
#endif

	m_scenes[scene->name()] = scene;
	scene->init();
}

void SceneManager::registerScene(const std::string& filename)
{
	Scene* newScene = new AnimSceneImpl(filename);
	m_ownerScenes.push_back(newScene);
	registerScene(newScene);
}

void SceneManager::switchToScene(const std::string& name, bool destroyStack)
{
    m_state = SWITCHING;
    m_nextSceneName = name;
    m_destroyStack = destroyStack;
	if (m_currentScene)
		m_currentScene->disappear();
}

void SceneManager::pushAndSwitchToScene(const std::string& name)
{
#ifdef DEBUG
    if (m_currentScene == NULL)
        throw std::runtime_error("SceneManager: Cannot push NULL scene");
#endif
    m_nextSceneName = name;
    m_state = PUSH_AND_SWITCHING;
}

void SceneManager::switchToPopedScene()
{
#ifdef DEBUG
    if (m_sceneStack.size() == 0)
        throw std::runtime_error("SceneManager: Cannot pop scene, stack is empty");
#endif
    m_state = POP;
    if (m_currentScene)
        m_currentScene->disappear();
}

void SceneManager::update(const double elapsedTime)
{
	if (m_currentScene)
		m_currentScene->update(elapsedTime);

    if (m_state != NOTHING) {
        switch(m_state) {
            case NOTHING:
                break;
            case SWITCHING:
                if (m_destroyStack) {
                    for(std::list<Scene*>::const_iterator it = m_sceneStack.begin(); it != m_sceneStack.end(); it++) {
                        Scene* scene = *it;
                        std::cout << "Switching: disappear(" << scene->name() << ")" << std::endl;
                        Core::telemetryManager().trackEvent("scene", "abort", scene->name(), 0);
                        scene->disappear();
                        scene->abort();
                        if (m_currentScene->usePlayingHud())
                            Core::hudManager().abortPlayingHud();
                    }
                    m_sceneStack.clear();
                }
                if (m_currentScene) {
                    m_currentScene->destroy();
                    Core::telemetryManager().trackEvent("scene", "destroy", m_currentScene->name(), 0);
                }
                m_currentScene = scene(m_nextSceneName);
                Core::telemetryManager().trackEvent("scene", "appear", m_nextSceneName, 0);
                break;
            case PUSH_AND_SWITCHING:
                if (m_currentScene) {
                    m_sceneStack.push_back(m_currentScene);
                    m_currentScene->pushed();
                    Core::telemetryManager().trackEvent("scene", "push", m_currentScene->name(), 0);
                }
                m_currentScene = scene(m_nextSceneName);
                Core::telemetryManager().trackEvent("scene", "appear", m_nextSceneName, 0);
                break;
            case POP:
                if (m_currentScene) {
                    m_currentScene->destroy();
                    Core::telemetryManager().trackEvent("scene", "destroy", m_currentScene->name(), 0);
                }
                m_currentScene = m_sceneStack.back();
                m_sceneStack.pop_back();
                if (m_currentScene != NULL)
                    Core::telemetryManager().trackEvent("scene", "pop", m_currentScene->name(), 0);
                break;
        }

        if (m_state != NOTHING)
            Core::telemetryManager().dispatchInfo();
        std::set<std::string> oldResourceGroupNames = m_loadedResourceGroupNames;
        std::list<std::string> newResourceGroupNames = deepGroupDependences(m_currentScene);
        
		for(std::list<Scene*>::const_iterator it = m_sceneStack.begin(); it != m_sceneStack.end(); it++) {
            Scene* scene = *it;
            const std::list<std::string>& resourceGroupNames = deepGroupDependences(scene);
            newResourceGroupNames.insert(newResourceGroupNames.end(), resourceGroupNames.begin(), resourceGroupNames.end());
        }
        
		// ToUnload = old - new
		// ToLoad = new - old
        // ToPreload = new.preload - ToUnload - ToLoad
        
		std::list<std::string> resourceGroupNamesToUnload;
		std::list<std::string> resourceGroupNamesToLoad;
        std::list<std::string> preloadResourceGroupNames;

        preloadResourceGroupNames = preloadDeepGroupDependences(m_currentScene);
    
		resourceGroupNamesToUnload.insert(resourceGroupNamesToUnload.end(), oldResourceGroupNames.begin(), oldResourceGroupNames.end());
		for(std::list<std::string>::const_iterator it = newResourceGroupNames.begin(); it != newResourceGroupNames.end(); it++) {
			resourceGroupNamesToUnload.remove(*it);
            preloadResourceGroupNames.remove(*it);
        }

		resourceGroupNamesToLoad = newResourceGroupNames;
		for(std::set<std::string>::const_iterator it = oldResourceGroupNames.begin(); it != oldResourceGroupNames.end(); it++) {
			resourceGroupNamesToLoad.remove(*it);
            preloadResourceGroupNames.remove(*it);
        }
		
        for(std::set<std::string>::const_iterator it = m_loadedResourceGroupNames.begin(); it != m_loadedResourceGroupNames.end(); it++) {
            newResourceGroupNames.remove(*it);
        }        

        Core::resourceManager().unloadResourceGroups(resourceGroupNamesToUnload);
        Core::resourceManager().preloadResourceGroups(preloadResourceGroupNames);
        Core::resourceManager().loadResourceGroups(resourceGroupNamesToLoad);
		
        for(std::list<std::string>::const_iterator it = resourceGroupNamesToUnload.begin(); it != resourceGroupNamesToUnload.end(); it++) {
            m_loadedResourceGroupNames.erase(*it);
        }
        m_loadedResourceGroupNames.insert(resourceGroupNamesToLoad.begin(), resourceGroupNamesToLoad.end());

        if (m_currentScene->usePlayingHud()) {
            Core::hudManager().usePlayingHud(m_currentScene->playingHudName(), true, m_currentScene->playingHudListener());
        } else
            Core::hudManager().disappearPlayingHud();

        switch(m_state) {
            case NOTHING:
                break;
            case SWITCHING:
                m_currentScene->appear();
                break;
            case PUSH_AND_SWITCHING:
                m_currentScene->appear();
                break;
            case POP:
                m_currentScene->poped();
                break;
        }
        
        std::cout << "Switch to scene '" << m_currentScene->name() << "'" << std::endl;
        std::cout << "Loaded resources: ";
        std::copy(m_loadedResourceGroupNames.begin(), m_loadedResourceGroupNames.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;
        m_state = NOTHING;
    }
}

Action* SceneManager::readFromXml(TiXmlElement* node)
{
    std::string prefix;
    const std::string& nodeValue = node->Value();
    size_t dots = nodeValue.find_first_of(':');
    if (dots == std::string::npos)
        prefix = "";
    else
        prefix = nodeValue.substr(0, dots);
    
    std::map<std::string, TemplateActionFactory*>::iterator it = m_factories.find(prefix);
    if (it == m_factories.end())
        throw std::runtime_error("SceneManager: factory with prefix '" + prefix + "' not registered");
    return it->second->readFromXml(prefix, node);
}

Scene* SceneManager::scene(const std::string& name)
{
#ifdef DEBUG
    std::map<std::string, Scene*>::iterator it = m_scenes.find(name);
    if ( it == m_scenes.end())
        throw std::runtime_error("SceneManager: scene not found '" + name + "'");
    return it->second;
#else
    return m_scenes[name];
#endif
}

const std::list<std::string> SceneManager::deepGroupDependences(Scene* scene)
{
    std::list<std::string> result;
    const std::list<std::string> groupNames = scene->resourceGroupNames();
    for(std::list<std::string>::const_iterator it = groupNames.begin(); it != groupNames.end(); it++) {
        std::list<std::string> childrenDeep = Core::resourceManager().deepGroupDependences(*it);
        for(std::list<std::string>::const_iterator it2 = childrenDeep.begin(); it2 != childrenDeep.end(); it2++) {
            if (std::find(result.begin(), result.end(), *it2) == result.end())
                result.push_back(*it2);
        }
    }
    return result;
}

const std::list<std::string> SceneManager::preloadDeepGroupDependences(Scene* scene)
{
    std::list<std::string> result;
    const std::list<std::string> groupNames = scene->preloadResourceGroupNames();
    for(std::list<std::string>::const_iterator it = groupNames.begin(); it != groupNames.end(); it++) {
        std::list<std::string> childrenDeep = Core::resourceManager().deepGroupDependences(*it);
        for(std::list<std::string>::const_iterator it2 = childrenDeep.begin(); it2 != childrenDeep.end(); it2++) {
            if (std::find(result.begin(), result.end(), *it2) == result.end())
                result.push_back(*it2);
        }
    }
    return result;
}


