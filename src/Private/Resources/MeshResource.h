#pragma once

#include <KYEngine/Mesh.h>
#include <KYEngine/Private/Resources/Resource.h>

class MeshResource
	: public Resource
	, public Mesh
{
public:
	MeshResource();
	virtual ~MeshResource();

// Resource partial implementation
public:
	const std::string& name() const { return m_name; }
	
protected:
	std::string m_name;
};