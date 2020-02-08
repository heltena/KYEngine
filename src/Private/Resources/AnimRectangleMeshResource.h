#pragma once

#include <tinyxml.h>

#include <KYEngine/Private/Resources/AnimRectangleFrameResource.h>
#include <KYEngine/Private/Resources/MeshResource.h>

#include <KYEngine/Texture.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/Vector4.h>

#include <vector>

class AnimRectangleMeshResource
	: public MeshResource
{
public:
	AnimRectangleMeshResource();
	virtual ~AnimRectangleMeshResource();
    
public:
	static const std::string XML_NODE;
	static AnimRectangleMeshResource* readFromXml(TiXmlElement* node);
	
// Resource implementation (partial in MeshImpl)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// Mesh implementation
public:
	int frameCount() const { return m_frames.size(); }
	void draw(double hpercent, int frame = 0);
	const Box& boundingBox() const;
    void addMeshDataTo(OptimizedMeshData& data);

private:
	void setName(const std::string& name) { m_name = name; }
	void setTextureName(const std::string& textureName) { m_textureName = textureName; }
    void setColor(const Vector4& color) { m_color = color; }
	void setNormal(const Vector4& normal) { m_normal = normal; }
	void setInverted(bool inverted) { m_inverted = inverted; }
	void addFrame(const AnimRectangleFrameResource& frame) { m_frames.push_back(frame); }
	
private:
	bool m_loaded;
	std::string m_textureName;
	Box m_boundingBox;
    Vector4 m_color;
	Vector4 m_normal;
	bool m_inverted;
	Texture* m_texture;
	std::vector<AnimRectangleFrameResource> m_frames;
	float *m_verts;
	float *m_coords;
	static const float DEFAULT_VERTS[4 * 4];
};