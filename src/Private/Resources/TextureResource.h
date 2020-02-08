#pragma once

#include <tinyxml.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <KYEngine/Private/Resources/Resource.h>
#include <KYEngine/Utility/DirectionEnum.h>

#include <pthread.h>
#include <string>

class TextureResource
	: public Resource
	, public Texture
{
public:
	TextureResource();
	virtual ~TextureResource();
    
public:
	static const std::string XML_NODE;
	static TextureResource* readFromXml(TiXmlElement* node);

// Resource implementation
public:
	const std::string& name() const { return m_name; }
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
private:
    static void* preload_thread(void* param);
    void load_private();
    
// Texture implementation
public:
	int width() const { return m_width; }
	int height() const { return m_height; }
	void bind();

private:
	void setName(const std::string& name) { m_name = name; }
	void setFilename(const std::string& filename) { m_filename = filename; }

private:
	std::string m_name;
	std::string m_filename;
	
    pthread_t m_thread;
    bool m_preloading;
	bool m_loaded;
	size_t m_width;
	size_t m_height;
    GLubyte* m_data;
	GLuint m_textureId;
};


