#pragma once

#include <KYEngine/HitContainer.h>

#include <map>
#include <string>

class Core;
class HitContainerImpl;

class HitManager
{
private:
	friend class Core;
	HitManager();
	virtual ~HitManager();
	
public:
	HitContainer* createContainer(const std::string& name, int zorder, const std::string& animMeshCollectionRef, const std::string& defaultAnimRef);
	bool containsContainer(const std::string& name);
	HitContainer* container(const std::string& name);
	void removeContainer(const std::string& name);

	void update(const double elapsedTime);

private:
    std::map<std::string, HitContainerImpl*> m_containers;
};