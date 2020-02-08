#pragma once

#include <KYEngine/Scene.h>
#include <KYEngine/Private/SceneTimeline.h>

#include <tinyxml.h>

#include <list>
#include <map>
#include <string>

class Entity;
class MeshEntityImpl;

class AnimSceneImpl
	: public Scene
{
public:
	AnimSceneImpl(const std::string& filename);
	virtual ~AnimSceneImpl();
	
private:
    void load();
    void unload();
    
// Scene partial implementation
public:
	virtual const std::string& name() const { return m_name; }
    virtual bool usePlayingHud() const { return m_timeline.usePlayingHud(); }
    virtual const std::string playingHudName() const { return m_timeline.playingHudName(); }  
    virtual PlayingHudListener* playingHudListener();
	virtual void init();
	virtual void appear();
	virtual void disappear();
    virtual void pushed();
    virtual void poped();
	virtual void destroy();
    virtual void abort();
	virtual void update(const double elapsedTime);
    const std::list<std::string>& preloadResourceGroupNames() const { return m_preloadResourceGroupNames; }
	const std::list<std::string>& resourceGroupNames() const { return m_resourceGroupNames; }

private:
    bool m_loaded;
    const std::string m_filename;
	std::string m_name;
    std::list<std::string> m_preloadResourceGroupNames;
	std::list<std::string> m_resourceGroupNames;
	SceneTimeline m_timeline;
};