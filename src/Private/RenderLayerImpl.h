#pragma once

#include <KYEngine/RenderLayer.h>

#include <list>
#include <set>

class Entity;
class RenderManager;

class RenderLayerImpl
	: public RenderLayer
{
private:
    friend class RenderManager;
	RenderLayerImpl(const std::string& name, int zorder, bool showing = true);
	virtual ~RenderLayerImpl();
	
private:
	struct SortEntities
	{
		bool operator()(const Entity* lhs, const Entity* rhs) const;
	};

// RenderLayer implementation
public:
    const std::string& name() const { return m_name; }
	void addEntity(Entity* entity, bool takeControl = false);
    void updateEntityPos(Entity* entity);
	void removeEntity(Entity* entity);
	void removeAllEntities();
    void removeAllEntities(const std::list<Entity*>& saveThese);
    void updateEntities(const std::list<Entity*>& toAdd, const std::list<Entity*>& toRemove);

	virtual void show() { m_showing = true; }
    virtual void hide() { m_showing = false; }
    virtual bool isShowing() const { return m_showing; }
    
	void update(const double elapsedTime);
	void render();

public:
    int zorder() const { return m_zorder; }
    void eraseOwnEntities();

private:
    const std::string m_name;
    const int m_zorder;
    bool m_showing;
	std::multiset<Entity*, SortEntities> m_entities;
    std::list<Entity*> m_ownEntities;
};