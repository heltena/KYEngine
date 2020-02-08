#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/RenderLayerImpl.h>

#include <iostream>
#include <list>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

RenderLayerImpl::RenderLayerImpl(const std::string& name, int zorder, bool showing)
    : m_name(name)
    , m_zorder(zorder)
    , m_showing(showing)
{
}

RenderLayerImpl::~RenderLayerImpl()
{
    removeAllEntities();
}

bool RenderLayerImpl::SortEntities::operator()(const Entity* lhs, const Entity* rhs) const
{
	return lhs->pos()[2] < rhs->pos()[2];
}

void RenderLayerImpl::update(const double elapsedTime)
{
	for(std::multiset<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
		Entity* entity = *it;
		entity->update(elapsedTime);
	}
}

void RenderLayerImpl::render()
{
    if (!m_showing)
        return;
#ifdef DEBUG 
    for(std::multiset<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
		Entity* entity = *it;
		if (entity == NULL)
			throw std::runtime_error("Entity error!");
    }
#endif

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    for(std::multiset<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
		Entity* entity = *it;
        entity->drawOpaque();
	}
    
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    for(std::multiset<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
		Entity* entity = *it;
        entity->drawSemiTransparent();
	}
    
    glDepthMask(GL_TRUE);
}

void RenderLayerImpl::addEntity(Entity* entity, bool takeControl)
{
#ifdef DEBUG
	if (entity == NULL)
		throw std::runtime_error("addEntity: entity is NULL");
#endif
	m_entities.insert(entity);
    if (takeControl)
        m_ownEntities.push_back(entity);
    entity->setLayer(this);
}

void RenderLayerImpl::updateEntityPos(Entity* entity)
{
    std::multiset<Entity*, SortEntities>::iterator it = m_entities.begin();
    while (it != m_entities.end() && *it != entity)
        it++;
    if (it != m_entities.end()) {
        m_entities.erase(it);
        m_entities.insert(entity);
    }
}

void RenderLayerImpl::removeEntity(Entity* entity)
{
    entity->setLayer(NULL);
    // TODO: optimize it, m_entities.erase(entity); doesn't work
    std::multiset<Entity*, SortEntities>::iterator it = m_entities.begin();
    while (it != m_entities.end() && *it != entity)
        it++;
    if (it != m_entities.end())
        m_entities.erase(it);
    std::list<Entity*>::iterator it2 = std::find(m_ownEntities.begin(), m_ownEntities.end(), entity);
    if (it2 != m_ownEntities.end()) {
        delete *it2;
        m_ownEntities.erase(it2);
    }
}

void RenderLayerImpl::removeAllEntities()
{
    for(std::multiset<Entity*, SortEntities>::iterator it = m_entities.begin(); it != m_entities.end(); it++) {
        Entity* entity = *it;
        entity->setLayer(NULL);
    }
    m_entities.clear();
    eraseOwnEntities();
}

void RenderLayerImpl::removeAllEntities(const std::list<Entity*>& saveThese)
{
    std::list<Entity*> toKill;

    for(std::multiset<Entity*, SortEntities>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
        toKill.push_back(*it);

    for(std::list<Entity*>::const_iterator it = saveThese.begin(); it != saveThese.end(); it++)
        toKill.remove(*it);
    
    for(std::list<Entity*>::const_iterator it = toKill.begin(); it != toKill.end(); it++)
        removeEntity(*it);
}

void RenderLayerImpl::updateEntities(const std::list<Entity*>& toAdd, const std::list<Entity*>& toRemove)
{
    std::list<Entity*> effToAdd = toAdd;
    for(std::list<Entity*>::const_iterator it = toRemove.begin(); it != toRemove.end(); it++)
        effToAdd.remove(*it);
    for(std::multiset<Entity*, SortEntities>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
        effToAdd.remove(*it);
    for(std::list<Entity*>::const_iterator it = effToAdd.begin(); it != effToAdd.end(); it++) {
        Entity* current = *it;
        m_entities.insert(current);
        current->setLayer(this);
    }
}

void RenderLayerImpl::eraseOwnEntities()
{
    for(std::list<Entity*>::iterator it = m_ownEntities.begin(); it != m_ownEntities.end(); it++) {
        Entity* entity = *it;
        entity->setLayer(NULL);
        m_entities.erase(entity);
        delete *it;
    }
    m_ownEntities.clear();
}