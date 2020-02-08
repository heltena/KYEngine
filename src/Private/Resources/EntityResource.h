#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/Private/Resources/Resource.h>

#include <string>

class AnimSceneFactory;
class Mesh;

class EntityResource
	: public Resource
	, public Entity
{
public:
	EntityResource();
	virtual ~EntityResource();

// Resource partial implementation
public:
	const std::string& name() const { return m_name; }
	
protected:
	std::string m_name;
};


