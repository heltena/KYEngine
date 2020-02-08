#include <KYEngine/Core.h>
#include <KYEngine/Private/Resources/ParallaxLayer.h>

#include <KYEngine/Utility/TiXmlHelper.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>
#include <stdexcept>

const std::string ParallaxLayer::XML_NODE = "parallax-layer";

ParallaxLayer::ParallaxLayer()
	: m_layer(NULL)
    , m_hpercent(1)
    , m_color(1.0, 1.0, 1.0, 1.0)
	, m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
    , m_z(0)
    , m_mesh(NULL)
    , m_width(1)
{
}

ParallaxLayer::ParallaxLayer(const ParallaxLayer& other)
    : m_name(other.m_name)
    , m_layer(NULL)
    , m_hpercent(other.m_hpercent)
    , m_color(other.m_color)
    , m_angle(other.m_angle)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    , m_z(other.m_z)
    , m_meshRef(other.m_meshRef)
    , m_mesh(other.m_mesh)
    , m_width(other.m_width)
{
}

ParallaxLayer::~ParallaxLayer()
{
}

ParallaxLayer* ParallaxLayer::readFromXml(TiXmlElement* node)
{
    ParallaxLayer* result = new ParallaxLayer();
    
    const std::string name = TiXmlHelper::readString(node, "name", false, "#LAYER-UNDEF");
    const double z = TiXmlHelper::readDouble(node, "z", true);
    const std::string& meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
    const double width = TiXmlHelper::readDouble(node, "width", true);

    result->setName(name);
    result->setZ(z);
    result->setMeshRef(meshRef);
    result->setUseBlending(useBlending);
    result->setWidth(width);
    
    return result;
}

void ParallaxLayer::load()
{
    m_mesh = Core::resourceManager().mesh(m_meshRef);
}

void ParallaxLayer::unload()
{
    m_mesh = NULL;
}

const Box& ParallaxLayer::screenBounds() const
{
	m_screenBounds = m_mesh->boundingBox();
	m_screenBounds.translate(m_pos);
	return m_screenBounds;
}

void ParallaxLayer::update(const double elapsedTime)
{
}

void ParallaxLayer::draw()
{
    if (m_mesh == NULL)
        return;
    glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    m_mesh->draw(m_hpercent);
	glPopMatrix();
}
