#include <KYEngine/Private/Resources/AnimRectangleMeshResource.h>

#include <KYEngine/Core.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cstdio>
#include <cstring>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string AnimRectangleMeshResource::XML_NODE = "anim-rectangle-mesh";

AnimRectangleMeshResource* AnimRectangleMeshResource::readFromXml(TiXmlElement* node)
{
    AnimRectangleMeshResource* result = new AnimRectangleMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string textureName = TiXmlHelper::readString(node, "texture-ref", true);
    bool inverted = TiXmlHelper::readBool(node, "inverted", false, false);
	const Vector4 color = TiXmlHelper::readVector(node, "r", "g", "b", "a", NO_READ, Vector4::WHITE);
    
	result->setName(name);
	result->setTextureName(textureName);
    result->setColor(color);
	result->setInverted(inverted);
	
	TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
		if (value == "frame") {
            // TODO: fix it!
            AnimRectangleFrameResource* newFrame = AnimRectangleFrameResource::readFromXml(curr);
			result->addFrame(*newFrame);
            delete(newFrame);
		} else
			throw std::runtime_error("loadAnimRectangleMesh(" + name + ") tag error: " + value);
        
		curr = curr->NextSiblingElement();
	}    return result;
}

const float AnimRectangleMeshResource::DEFAULT_VERTS[] = {
	-0.5f, -0.5f, 0, 1,
	0.5f, -0.5f, 0, 1,
	-0.5f,  0.5f, 0, 1,
	0.5f,  0.5f, 0, 1,
};

AnimRectangleMeshResource::AnimRectangleMeshResource()
	: m_texture(NULL)
	, m_verts(NULL)
	, m_coords(NULL)
	, m_boundingBox(-0.5f, -0.5f, 1.0f, 1.0f)
    , m_color(1, 1, 1, 1)
	, m_normal(0.0f, 0.0f, 1.0f)
	, m_inverted(false)
{
}

AnimRectangleMeshResource::~AnimRectangleMeshResource()
{
}

void AnimRectangleMeshResource::preload()
{
    // TODO: preload
}

void AnimRectangleMeshResource::unloadFromPreloaded()
{
}

void AnimRectangleMeshResource::load()
{
	m_texture = Core::resourceManager().texture(m_textureName);
	
    if (m_coords != NULL || m_verts != NULL)
        throw std::runtime_error("AnimRectangleMeshResource: coords or verts reused!");
	int frameCount = m_frames.size();
	m_coords = new float[4 * 2 * frameCount];
	m_verts = new float[4 * 4 * frameCount];
	int coffset = 0;
	int voffset = 0;
	for(std::vector<AnimRectangleFrameResource>::iterator it = m_frames.begin(); it != m_frames.end(); it++) {
		const Box& box = it->box();
        const Vector4& pivot = it->pivot();
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
		m_coords[ia * 2 + 0 + coffset] = box.left() / m_texture->width();
		m_coords[ia * 2 + 1 + coffset] = (box.top() + box.height()) / m_texture->height();
	
		m_coords[ib * 2 + 0 + coffset] = (box.left() + box.width()) / m_texture->width();
		m_coords[ib * 2 + 1 + coffset] = (box.top() + box.height()) / m_texture->height();
	
		m_coords[ic * 2 + 0 + coffset] = box.left() / m_texture->width();
		m_coords[ic * 2 + 1 + coffset] = box.top() / m_texture->height();
	
		m_coords[id * 2 + 0 + coffset] = (box.left() + box.width()) / m_texture->width();
		m_coords[id * 2 + 1 + coffset] = box.top() / m_texture->height();
		
		coffset += 4 * 2;
		
		const Vector4& size = it->size();
		for(int i = 0; i < 4; i++) {
			m_verts[i * 4 + 0 + voffset] = DEFAULT_VERTS[i * 4 + 0] * size[0] - pivot[0];
			m_verts[i * 4 + 1 + voffset] = DEFAULT_VERTS[i * 4 + 1] * size[1] - pivot[1];
			m_verts[i * 4 + 2 + voffset] = DEFAULT_VERTS[i * 4 + 2];
			m_verts[i * 4 + 3 + voffset] = DEFAULT_VERTS[i * 4 + 3];
		}
		voffset += 4 * 4;
	}
}

void AnimRectangleMeshResource::unload()
{
	m_texture = NULL;
	delete[] m_coords;
	m_coords = NULL;
	delete[] m_verts;
	m_verts = NULL;
}

void AnimRectangleMeshResource::draw(double hpercent, int frame)
{
    // TODO: hpercent
	glEnable(GL_TEXTURE_2D);
	m_texture->bind();
	
	glVertexPointer(4, GL_FLOAT, 0, m_verts + frame * 4 * 4);
    glEnableClientState(GL_VERTEX_ARRAY);
	
    glDisableClientState(GL_COLOR_ARRAY);
    float currColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currColor);
	glColor4f(currColor[0] * m_color[0], currColor[1] * m_color[1], currColor[2] * m_color[2], currColor[3] * m_color[3]);
    
	glTexCoordPointer(2, GL_FLOAT, 0, m_coords + frame * 4 * 2);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glNormal3f(m_normal[0], m_normal[1], m_normal[2]);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glColor4f(1, 1, 1, 1);
}

const Box& AnimRectangleMeshResource::boundingBox() const
{
    // TODO:
    return m_frames[0].boundingBox();
}

void AnimRectangleMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    throw std::runtime_error("AnimRectangleMeshResource cannot be used in OptimizedMeshData");
}

