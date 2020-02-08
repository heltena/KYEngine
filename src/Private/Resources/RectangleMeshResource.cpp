#include <KYEngine/Private/Resources/RectangleMeshResource.h>

#include <KYEngine/Core.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string RectangleMeshResource::XML_NODE = "rectangle-mesh";

RectangleMeshResource* RectangleMeshResource::readFromXml(TiXmlElement* node)
{
    RectangleMeshResource* result = new RectangleMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string textureName = TiXmlHelper::readString(node, "texture-ref", true);
    const Box box = TiXmlHelper::readBox(node, "tx", "ty", "tw", "th", READ_ALL_BOX);
    const Vector4 size = TiXmlHelper::readVector(node, "w", "h", "", "", NO_READ, box.width(), box.height());
	const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0.0f, 0.0f);
    const bool inverted = TiXmlHelper::readBool(node, "inverted", false, false);
    
	result->setName(name);
	result->setTextureName(textureName);
	result->setBox(box);
	result->setSize(size);
    result->setPivot(pivot);
    result->setInverted(inverted);
    
    return result;
}

const float RectangleMeshResource::DEFAULT_VERTS[] = {
	-0.5f, -0.5f, 0, 1,
	 0.5f, -0.5f, 0, 1,
	-0.5f,  0.5f, 0, 1,
	 0.5f,  0.5f, 0, 1,
};

RectangleMeshResource::RectangleMeshResource()
	: m_texture(NULL)
	, m_box(0.0f, 0.0f, 1.0f, 1.0f)
	, m_size(1.0f, 1.0f)
    , m_pivot(0.0f, 0.0f)
	, m_boundingBox(-0.5f, -0.5f, 1.0f, 1.0f)
	, m_normal(0.0f, 0.0f, 1.0f)
{
}

RectangleMeshResource::~RectangleMeshResource()
{
}

void RectangleMeshResource::preload()
{
}

void RectangleMeshResource::unloadFromPreloaded()
{
}

void RectangleMeshResource::load()
{
	m_texture = Core::resourceManager().texture(m_textureName);
	
    int ia, ib, ic, id;
    if (! m_inverted) {
        ia = 0;
        ib = 1;
        ic = 2;
        id = 3;
    } else {
        ia = 1;
        ib = 0;
        ic = 3;
        id = 2;
    }
	
    m_coords[ia * 2 + 0] = m_box.left() / m_texture->width();
	m_coords[ia * 2 + 1] = (m_box.top() + m_box.height()) / m_texture->height();
	
	m_coords[ib * 2 + 0] = (m_box.left() + m_box.width()) / m_texture->width();
	m_coords[ib * 2 + 1] = (m_box.top() + m_box.height()) / m_texture->height();
	
	m_coords[ic * 2 + 0] = m_box.left() / m_texture->width();
	m_coords[ic * 2 + 1] = m_box.top() / m_texture->height();
	
	m_coords[id * 2 + 0] = (m_box.left() + m_box.width()) / m_texture->width();
	m_coords[id * 2 + 1] = m_box.top() / m_texture->height();

	for(int i = 0; i < 4; i++) {
		m_verts[i * 4 + 0] = DEFAULT_VERTS[i * 4 + 0] * m_size[0] - m_pivot[0];
		m_verts[i * 4 + 1] = DEFAULT_VERTS[i * 4 + 1] * m_size[1] - m_pivot[1];
		m_verts[i * 4 + 2] = DEFAULT_VERTS[i * 4 + 2];
		m_verts[i * 4 + 3] = DEFAULT_VERTS[i * 4 + 3];
	}
}

void RectangleMeshResource::unload()
{
	m_texture = NULL;
}

void RectangleMeshResource::setSize(const Vector4& size)
{
	m_size = size;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void RectangleMeshResource::setPivot(const Vector4& pivot)
{
    m_pivot = pivot;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void RectangleMeshResource::draw(double hpercent, int frame)
{
    if (hpercent == 0 || m_texture == NULL)
        return;

    glEnable(GL_TEXTURE_2D);
	m_texture->bind();
	
    if (hpercent == 1) {
        glVertexPointer(4, GL_FLOAT, 0, m_verts);
        glTexCoordPointer(2, GL_FLOAT, 0, m_coords);
    } else {
        float verts[4 * 4];
        float coords[4 * 2];
        double m;
        if (hpercent > 1)
            m = 1;
        else if (hpercent < -1)
            m = 1;
        else
            m = hpercent > 0 ? 1.0 - hpercent : 1.0 + hpercent;

        double lm = hpercent < 0 ? m : 0;
        double rm = hpercent > 0 ? m : 0;

        memcpy(verts, m_verts, sizeof(verts));
        memcpy(coords, m_coords, sizeof(coords));
        
        coords[0 * 2 + 0] = (m_box.left() + lm * m_box.width()) / m_texture->width();
        coords[1 * 2 + 0] = (m_box.left() + (1 - rm) * m_box.width()) / m_texture->width();
        coords[2 * 2 + 0] = (m_box.left() + lm * m_box.width())/ m_texture->width();
        coords[3 * 2 + 0] = (m_box.left() + (1 - rm) * m_box.width()) / m_texture->width();
        
        verts[0 * 4 + 0] = (DEFAULT_VERTS[0 * 4 + 0] + lm) * m_size[0] - m_pivot[0];
        verts[1 * 4 + 0] = (DEFAULT_VERTS[1 * 4 + 0] - rm) * m_size[0] - m_pivot[0];
        verts[2 * 4 + 0] = (DEFAULT_VERTS[2 * 4 + 0] + lm) * m_size[0] - m_pivot[0];
        verts[3 * 4 + 0] = (DEFAULT_VERTS[3 * 4 + 0] - rm) * m_size[0] - m_pivot[0];
        
        glVertexPointer(4, GL_FLOAT, 0, verts);
        glTexCoordPointer(2, GL_FLOAT, 0, coords);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glNormal3f(m_normal[0], m_normal[1], m_normal[2]);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void RectangleMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    Vector4 v0(m_verts[4 * 0 + 0], m_verts[4 * 0 + 1], m_verts[4 * 0 + 2], m_verts[4 * 0 + 3]);
    Vector4 v1(m_verts[4 * 1 + 0], m_verts[4 * 1 + 1], m_verts[4 * 1 + 2], m_verts[4 * 1 + 3]);
    Vector4 v2(m_verts[4 * 2 + 0], m_verts[4 * 2 + 1], m_verts[4 * 2 + 2], m_verts[4 * 2 + 3]);
    Vector4 v3(m_verts[4 * 3 + 0], m_verts[4 * 3 + 1], m_verts[4 * 3 + 2], m_verts[4 * 3 + 3]);
    
    Vector4 tc0(m_coords[2 * 0 + 0], m_coords[2 * 0 + 1]);
    Vector4 tc1(m_coords[2 * 1 + 0], m_coords[2 * 1 + 1]);
    Vector4 tc2(m_coords[2 * 2 + 0], m_coords[2 * 2 + 1]);
    Vector4 tc3(m_coords[2 * 3 + 0], m_coords[2 * 3 + 1]);
 
    data.addFullVertexData(m_texture, v0, tc0);
    data.addFullVertexData(m_texture, v1, tc1);
    data.addFullVertexData(m_texture, v2, tc2);
    
    data.addFullVertexData(m_texture, v1, tc1);
    data.addFullVertexData(m_texture, v2, tc2);
    data.addFullVertexData(m_texture, v3, tc3);
}
