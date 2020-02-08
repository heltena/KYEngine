#include <KYEngine/Core.h>
#include <KYEngine/Managers/HitManager.h>
#include <KYEngine/Private/Hits/HitContainerImpl.h>

HitManager::HitManager()
{
}

HitManager::~HitManager()
{
}

HitContainer* HitManager::createContainer(const std::string& name, int zorder, const std::string& animMeshCollectionRef, const std::string& defaultAnimRef)
{
#ifdef DEBUG 
	if (m_containers.find(name) != m_containers.end())
		throw std::runtime_error("Container exists: " + name);
#endif
    HitContainerImpl* result = new HitContainerImpl(name, zorder, animMeshCollectionRef, defaultAnimRef);
    m_containers[name] = result;
    return result;
}

bool HitManager::containsContainer(const std::string& name)
{
    return m_containers.find(name) != m_containers.end();
}

HitContainer* HitManager::container(const std::string& name)
{
#ifdef DEBUG
	if (m_containers.find(name) == m_containers.end())
		throw std::runtime_error("Container not created: " + name);
#endif
	return m_containers[name];
}

void HitManager::removeContainer(const std::string& name)
{
#ifdef DEBUG
	if (m_containers.find(name) == m_containers.end())
		throw std::runtime_error("Container not created before: " + name);
#endif
    HitContainerImpl* toKill = m_containers[name];
	m_containers.erase(name);
    delete toKill;
}

void HitManager::update(const double elapsedTime)
{
    for(std::map<std::string, HitContainerImpl*>::const_iterator it = m_containers.begin(); it != m_containers.end(); it++) {
        HitContainerImpl* current = it->second;
        current->update(elapsedTime);
    }
}
