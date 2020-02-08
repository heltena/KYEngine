#pragma once

#include <KYEngine/TemplateActionFactory.h>
#include <KYEngine/Touch.h>

#include <list>
#include <map>
#include <set>
#include <string>

class AnimSceneActionFactory;
class Core;
class Scene;

class SceneManager
{
private:
    enum StateEnum
    {
        NOTHING,
        SWITCHING,
        PUSH_AND_SWITCHING,
        POP,
    };
private:
	friend class Core;
	SceneManager();
	virtual ~SceneManager();

public:
    void registerLibrary(const std::string& prefix, TemplateActionFactory* factory);
	void registerAnimScenes(const std::string& filename);
    
	void registerScene(Scene* scene);
	void registerScene(const std::string& filename);
	void switchToScene(const std::string& name, bool destroyStack = true);
    void pushAndSwitchToScene(const std::string& name);
    void switchToPopedScene();
	void update(const double elapsedTime);

private:
    friend class AnimSceneImpl;
    Action* readFromXml(TiXmlElement* node);
    Scene* scene(const std::string& name);

    const std::list<std::string> deepGroupDependences(Scene* scene);
    const std::list<std::string> preloadDeepGroupDependences(Scene* scene);

private:
    AnimSceneActionFactory* m_primarySceneFactory;
    std::map<std::string, TemplateActionFactory*> m_factories;
	std::list<Scene*> m_ownerScenes;
	std::map<std::string, Scene*> m_scenes;
    std::set<std::string> m_loadedResourceGroupNames;
    std::list<Scene*> m_sceneStack;
    bool m_clearSceneStack;
    Scene* m_currentScene;
	std::string m_nextSceneName;
    bool m_destroyStack;
	StateEnum m_state;
};
