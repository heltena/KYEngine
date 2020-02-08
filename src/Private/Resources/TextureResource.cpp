#include <KYEngine/Core.h>
#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Natives/NativeAutoreleasePool.h>
#include <KYEngine/Private/Resources/TextureResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <png++/png.hpp>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>

const std::string TextureResource::XML_NODE = "texture";

TextureResource* TextureResource::readFromXml(TiXmlElement* node)
{
    TextureResource* result = new TextureResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string filename = TiXmlHelper::readString(node, "filename", true);
	
	result->setName(name);
	result->setFilename(filename);
    return result;
}

TextureResource::TextureResource()
	: m_preloading(false)
    , m_loaded(false)
{
}

TextureResource::~TextureResource()
{
    if (m_preloading) {
        pthread_join(m_thread, NULL);
        free(m_data);
    }
        
	if (m_loaded)
		glDeleteTextures(1, &m_textureId);
}

void TextureResource::preload()
{
    if (m_preloading)
        return;
    m_preloading = true;
    pthread_create(&m_thread, NULL, TextureResource::preload_thread, this);
}

void TextureResource::unloadFromPreloaded()
{
    load();
    unload();
}

void* TextureResource::preload_thread(void* param)
{
    TextureResource* self = (TextureResource*)param;
    NativeAutoreleasePool pool;
    self->load_private();
    return NULL;
}

void TextureResource::load()
{
	if (m_loaded)
		throw std::runtime_error("Cannot load again this texture");
	
    if (m_preloading) {
        pthread_join(m_thread, NULL);
        m_preloading = false;
    } else
        load_private();

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    int err = glGetError();
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    glGenerateMipmapOES(GL_TEXTURE_2D);

    free(m_data);
    m_data = NULL;
    err = glGetError();

	m_loaded = true;
}

class TextureResourcePNGConsumer
    : public png::consumer<png::rgba_pixel, TextureResourcePNGConsumer>
{
public:
    TextureResourcePNGConsumer(png::image_info& info)
        : png::consumer<png::rgba_pixel, TextureResourcePNGConsumer>(info)
        , m_data(NULL)
        , m_width(0)
        , m_height(0)
    {
    }

    void reset(size_t pass)
    {
        png::image_info& xinfo = get_info();
        m_width = xinfo.get_width();
        m_height = xinfo.get_height();
        m_data = (GLubyte*) malloc(m_width * m_height * 4);
    }
    
    png::byte* get_next_row(size_t pos)
    {
        return reinterpret_cast<png::byte*>(m_data + pos * m_width * 4);
    }

    int width() { return m_width; }
    int height() { return m_height; }
    GLubyte* data() { return m_data; }

protected:
    GLubyte* m_data;
    size_t m_width;
    size_t m_height;
};

void TextureResource::load_private()
{
    png::image_info m_info;
    TextureResourcePNGConsumer consumer(m_info);
    std::ifstream file(filenamePath(m_filename).c_str(), std::ios::binary);
    consumer.read(file);
    m_width = consumer.width();
    m_height = consumer.height();
    m_data = consumer.data();
}

void TextureResource::unload()
{
    if (m_preloading) {
        pthread_join(m_thread, NULL);
        m_preloading = false;
        free(m_data);
        m_data = NULL;
    }

	if (!m_loaded)
		throw std::runtime_error("Cannot unload again this texture");
        
    glDeleteTextures(1, &m_textureId);
	m_textureId = 0;
	m_loaded = false;
}

void TextureResource::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}