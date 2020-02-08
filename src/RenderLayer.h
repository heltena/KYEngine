#pragma once

#include <string>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>

class Entity;
class RenderManager;

class RenderLayer
{
public:
    virtual ~RenderLayer() { }

    virtual const std::string& name() const = 0;
	virtual void addEntity(Entity* entity, bool takeControl = false) = 0;
    virtual void updateEntityPos(Entity* entity) = 0;
	virtual void removeEntity(Entity* entity) = 0;
    virtual void removeAllEntities() = 0;
    virtual void removeAllEntities(const std::list<Entity*>& saveThese) = 0;
    virtual void updateEntities(const std::list<Entity*>& toAdd, const std::list<Entity*>& toRemove) = 0;

	virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isShowing() const = 0;
    
protected:
	friend class RenderManager;
	virtual void update(const double elapsedTime) = 0;
	virtual void render() = 0;
};
