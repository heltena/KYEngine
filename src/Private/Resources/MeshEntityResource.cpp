#include <KYEngine/Core.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/Private/Resources/MeshEntityResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>

const std::string MeshEntityResource::XML_NODE = "mesh-entity";

MeshEntityResource* MeshEntityResource::readFromXml(TiXmlElement* node)
{
    MeshEntityResource* result = new MeshEntityResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", NO_READ, 0.0, 0.0, 0.0, 1.0);
    const double initialHPercent = TiXmlHelper::readDouble(node, "ihpercent", false, 1);
    const Vector4 color = TiXmlHelper::readVector(node, "ir", "ig", "ib", "ia", NO_READ, 1.0, 1.0, 1.0, 1.0);
	double angle = TiXmlHelper::readDouble(node, "angle", false, 0);
    bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
	result->setName(name);
	result->setMeshRef(meshRef);
	result->setInitialPos(initialPos);
    result->setInitialHPercent(initialHPercent);
    result->setColor(color);
    result->setAngle(angle);
    result->setUseBlending(useBlending);
    
    return result;
}

MeshEntityResource::MeshEntityResource()
	: m_layer(NULL)
    , m_hpercent(1)
    , m_color(1.0, 1.0, 1.0, 1.0)
	, m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_initialHPercent(1)
    , m_useBlending(false)
{
}

MeshEntityResource::~MeshEntityResource()
{
}

void MeshEntityResource::preload()
{
}

void MeshEntityResource::unloadFromPreloaded()
{
    m_mesh = NULL;
}

void MeshEntityResource::load()
{
	m_mesh = Core::resourceManager().mesh(m_meshRef);
    m_pos = m_initialPos;
    m_hpercent = m_initialHPercent;
    m_layer = NULL;
}

void MeshEntityResource::unload()
{
	m_mesh = NULL;
    m_layer = NULL;
}

const Box& MeshEntityResource::screenBounds() const
{
	m_screenBounds = m_mesh->boundingBox();
	m_screenBounds.translate(m_pos);
	return m_screenBounds;
}

void MeshEntityResource::update(const double elapsedTime)
{
}

void MeshEntityResource::draw()
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
