#pragma once

#include <tinyxml.h>

#include <KYEngine/AnimMeshCollection.h>
#include <KYEngine/Private/Resources/AnimMeshInfoInternal.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/Private/Resources/Resource.h>

#include <map>
#include <string>

class AnimMeshCollectionResource
	: public AnimMeshCollection
    , public Resource
{
public:
	AnimMeshCollectionResource();
	virtual ~AnimMeshCollectionResource();

public:
	static const std::string XML_NODE;
	static AnimMeshCollectionResource* readFromXml(TiXmlElement* node);

// Resource implementation
public:
	const std::string& name() const { return m_name; }
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
    
// AnimMeshCollection implementation
public:
    const std::string& defaultAnimRef() const { return m_defaultAnimRef; }
	int animCount() const { return m_anims.size(); }
    AnimMeshInfo* animMesh(const std::string& name);
   
private:
	void setName(const std::string& name) { m_name = name; }
	void setDefaultAnimRef(const std::string& defaultAnimRef) { m_defaultAnimRef = defaultAnimRef; }
	void addAnim(const std::string& name, const std::string& animMeshRef, double fps, bool loop);

private:
    std::string m_name;
	std::string m_defaultAnimRef;
	std::map<std::string, AnimMeshInfoInternal> m_anims;
};
