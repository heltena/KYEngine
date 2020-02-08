#include <KYEngine/Core.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/Private/Resources/AnimMeshCollectionResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>
#include <stdexcept>

const std::string AnimMeshCollectionResource::XML_NODE = "anim-mesh-collection";

AnimMeshCollectionResource* AnimMeshCollectionResource::readFromXml(TiXmlElement* node)
{
    AnimMeshCollectionResource* result = new AnimMeshCollectionResource();
    
    const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string defaultAnimRef = TiXmlHelper::readString(node, "default-anim-ref", true);

	result->setName(name);
	result->setDefaultAnimRef(defaultAnimRef);
	
	TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
		if (value == "anim") {
			const std::string& name = TiXmlHelper::readString(curr, "name", true);
			const std::string& meshRef = TiXmlHelper::readString(curr, "anim-mesh-ref", true);
            const double fps = TiXmlHelper::readDouble(curr, "fps", true);
            const bool loop = TiXmlHelper::readBool(curr, "loop", true);
            result->addAnim(name, meshRef, fps, loop);
		} else
			throw std::runtime_error("loadAnimMeshEntity(" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
    return result;
}

AnimMeshCollectionResource::AnimMeshCollectionResource()
{
}

AnimMeshCollectionResource::~AnimMeshCollectionResource()
{
}

void AnimMeshCollectionResource::preload()
{
	for(std::map<std::string, AnimMeshInfoInternal>::iterator it = m_anims.begin(); it != m_anims.end(); it++) {
        it->second.preload();
	}
}

void AnimMeshCollectionResource::unloadFromPreloaded()
{
	for(std::map<std::string, AnimMeshInfoInternal>::iterator it = m_anims.begin(); it != m_anims.end(); it++) {
        it->second.unloadFromPreloaded();
	}    
}

void AnimMeshCollectionResource::load()
{
	for(std::map<std::string, AnimMeshInfoInternal>::iterator it = m_anims.begin(); it != m_anims.end(); it++) {
        it->second.load();
	}
}

void AnimMeshCollectionResource::unload()
{
	for(std::map<std::string, AnimMeshInfoInternal>::iterator it = m_anims.begin(); it != m_anims.end(); it++) {
        it->second.unload();
	}
}

AnimMeshInfo* AnimMeshCollectionResource::animMesh(const std::string& name)
{
#ifdef DEBUG 
	if (m_anims.find(name) == m_anims.end())
        throw std::runtime_error("AnimMeshCollectionResource hasn't a anim called '" + name + "'");
#endif
    return &m_anims[name];
}

void AnimMeshCollectionResource::addAnim(const std::string& name, const std::string& animMeshRef, double fps, bool loop)
{
#ifdef DEBUG 
	if (m_anims.find(name) != m_anims.end())
		throw std::runtime_error("AnimMeshCollectionResource has a anim called '" + name + "'");
#endif
	m_anims[name] = AnimMeshInfoInternal(animMeshRef, fps, loop);
}
