#include <KYEngine/Private/Resources/GradientRectangleMeshResource.h>

#include <KYEngine/Core.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string GradientRectangleMeshResource::XML_NODE = "gradient-rectangle-mesh";

GradientRectangleMeshResource* GradientRectangleMeshResource::readFromXml(TiXmlElement* node)
{
    GradientRectangleMeshResource* result = new GradientRectangleMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
    const Vector4 size = TiXmlHelper::readVector(node, "w", "h", "", "", READ_X | READ_Y);
    const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0, 0);
	const Vector4 topLeftColor     = TiXmlHelper::readVector(node, "tlr", "tlg", "tlb", "tla", READ_ALL_VECTOR);
	const Vector4 topRightColor    = TiXmlHelper::readVector(node, "trr", "trg", "trb", "tra", READ_ALL_VECTOR);
	const Vector4 bottomLeftColor  = TiXmlHelper::readVector(node, "blr", "blg", "blb", "bla", READ_ALL_VECTOR);
	const Vector4 bottomRightColor = TiXmlHelper::readVector(node, "brr", "brg", "brb", "bra", READ_ALL_VECTOR);
    
	result->setName(name);
	result->setSize(size);
    result->setPivot(pivot);
    result->setTopLeftColor(topLeftColor);
    result->setTopRightColor(topRightColor);
    result->setBottomLeftColor(bottomLeftColor);
    result->setBottomRightColor(bottomRightColor);
    
    return result;
}

const float GradientRectangleMeshResource::DEFAULT_VERTS[] = {
	-0.5f, -0.5f, 0, 1,
	0.5f, -0.5f, 0, 1,
	-0.5f,  0.5f, 0, 1,
	0.5f,  0.5f, 0, 1,
};

GradientRectangleMeshResource::GradientRectangleMeshResource()
	: m_size(1.0f, 1.0f)
	, m_boundingBox(-0.5f, -0.5f, 1.0f, 1.0f)
	, m_normal(0.0f, 0.0f, 1.0f)
{
}

GradientRectangleMeshResource::~GradientRectangleMeshResource()
{
}

void GradientRectangleMeshResource::setSize(const Vector4& size)
{
	m_size = size;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void GradientRectangleMeshResource::setPivot(const Vector4& pivot)
{
    m_pivot = pivot;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void GradientRectangleMeshResource::preload()
{
}

void GradientRectangleMeshResource::unloadFromPreloaded()
{
}

void GradientRectangleMeshResource::load()
{
    for(int i = 0; i < 4; i++) {
        m_colors[0 * 4 + i] = (unsigned char) (255.0 * m_bottomLeftColor[i]);
        m_colors[1 * 4 + i] = (unsigned char) (255.0 * m_bottomRightColor[i]);
        m_colors[2 * 4 + i] = (unsigned char) (255.0 * m_topLeftColor[i]);
        m_colors[3 * 4 + i] = (unsigned char) (255.0 * m_topRightColor[i]);

		m_verts[i * 4 + 0] = DEFAULT_VERTS[i * 4 + 0] * m_size[0] - m_pivot[0];
		m_verts[i * 4 + 1] = DEFAULT_VERTS[i * 4 + 1] * m_size[1] - m_pivot[1];
		m_verts[i * 4 + 2] = DEFAULT_VERTS[i * 4 + 2];
		m_verts[i * 4 + 3] = DEFAULT_VERTS[i * 4 + 3];
	}
}

void GradientRectangleMeshResource::unload()
{
}

void GradientRectangleMeshResource::draw(double hpercent, int frame)
{
    // TODO: draw hpercent!
	glDisable(GL_TEXTURE_2D);
	
	glVertexPointer(4, GL_FLOAT, 0, m_verts);
    glEnableClientState(GL_VERTEX_ARRAY);
	
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, m_colors);
    glEnableClientState(GL_COLOR_ARRAY);
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glNormal3f(m_normal[0], m_normal[1], m_normal[2]);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void GradientRectangleMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    throw std::runtime_error("GradientRectangleMeshResource cannot be used in OptimizedMeshData");
}
