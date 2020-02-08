#pragma once

#include <KYEngine/PlayingHudListener.h>
#include <KYEngine/Touch.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>
#include <map>
#include <string>

class Entity;
class PlayingHud;

class Scene
{
public:
    virtual ~Scene() { }
	virtual const std::string& name() const = 0;
    virtual bool usePlayingHud() const = 0;
    virtual const std::string playingHudName() const = 0;
    virtual PlayingHudListener* playingHudListener() = 0;
	virtual void init() = 0;		// It only is called at the beginning
	virtual void appear() = 0;		// It is called when it appears
	virtual void disappear() = 0;	// It is called when it needs to disappear
    virtual void pushed() = 0;      // It is called when it change to "paused" scene like
    virtual void poped() = 0;       // It is called when it restores it state
	virtual void destroy() = 0;		// It is called every time it disappears definitively
    virtual void abort() = 0;       // It is called when it comes back to the menu
	virtual void update(const double elapsedTime) = 0;
    virtual const std::list<std::string>& preloadResourceGroupNames() const = 0;
	virtual const std::list<std::string>& resourceGroupNames() const = 0;
};
