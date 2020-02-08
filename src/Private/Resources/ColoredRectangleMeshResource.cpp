#include <KYEngine/Private/Resources/ColoredRectangleMeshResource.h>

#include <KYEngine/Core.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string ColoredRectangleMeshResource::XML_NODE = "colored-rectangle-mesh";

ColoredRectangleMeshResource* ColoredRectangleMeshResource::readFromXml(TiXmlElement* node)
{
    ColoredRectangleMeshResource* result = new ColoredRectangleMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
    const Vector4 size = TiXmlHelper::readVector(node, "w", "h", "", "", READ_X | READ_Y);
    const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0, 0);
	
	result->setName(name);
	result->setSize(size);
    result->setPivot(pivot);
    
    return result;
}

const float ColoredRectangleMeshResource::DEFAULT_VERTS[] = {
	-0.5f, -0.5f, 0, 1,
	0.5f, -0.5f, 0, 1,
	-0.5f,  0.5f, 0, 1,
	0.5f,  0.5f, 0, 1,
};

ColoredRectangleMeshResource::ColoredRectangleMeshResource()
	: m_size(1.0f, 1.0f)
	, m_boundingBox(-0.5f, -0.5f, 1.0f, 1.0f)
	, m_normal(0.0f, 0.0f, 1.0f)
{
}

ColoredRectangleMeshResource::~ColoredRectangleMeshResource()
{
}

void ColoredRectangleMeshResource::setSize(const Vector4& size)
{
	m_size = size;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void ColoredRectangleMeshResource::setPivot(const Vector4& pivot)
{
    m_pivot = pivot;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void ColoredRectangleMeshResource::preload()
{
    // TODO: preload
}

void ColoredRectangleMeshResource::unloadFromPreloaded()
{
}

void ColoredRectangleMeshResource::load()
{
	for(int i = 0; i < 4; i++) {
		m_verts[i * 4 + 0] = DEFAULT_VERTS[i * 4 + 0] * m_size[0] - m_pivot[0];
		m_verts[i * 4 + 1] = DEFAULT_VERTS[i * 4 + 1] * m_size[1] - m_pivot[1];
		m_verts[i * 4 + 2] = DEFAULT_VERTS[i * 4 + 2];
		m_verts[i * 4 + 3] = DEFAULT_VERTS[i * 4 + 3];
	}
}

void ColoredRectangleMeshResource::unload()
{
}

void ColoredRectangleMeshResource::draw(double hpercent, int frame)
{
    // TODO: draw hpercent!
	glDisable(GL_TEXTURE_2D);
	
	glVertexPointer(4, GL_FLOAT, 0, m_verts);
    glEnableClientState(GL_VERTEX_ARRAY);
	
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
    
	glNormal3f(m_normal[0], m_normal[1], m_normal[2]);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ColoredRectangleMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    throw std::runtime_error("ColoredRectangleMeshResource cannot be used in OptimizedMeshData");
}

