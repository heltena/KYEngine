#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Utility/DirectionEnum.h>
#include <KYEngine/Utility/Vector4.h>

class RectangleMeshResource
	: public MeshResource
{
public:
	RectangleMeshResource();
	virtual ~RectangleMeshResource();
    
public:
	static const std::string XML_NODE;
	static RectangleMeshResource* readFromXml(TiXmlElement* node);

// Resource implementation (partial in MeshImpl)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// Mesh implementation
public:
	int frameCount() const { return 1; }
	void draw(double hpercent, int frame = 0);
	const Box& boundingBox() const { return m_boundingBox; }
    void addMeshDataTo(OptimizedMeshData& data);

private:
	void setName(const std::string& name) { m_name = name; }
	void setTextureName(const std::string& textureName) { m_textureName = textureName; }
	void setBox(const Box& box) { m_box = box; }
	void setSize(const Vector4& size);
    void setPivot(const Vector4& pivot);
	void setNormal(const Vector4& normal) { m_normal = normal; }
	void setInverted(bool inverted) { m_inverted = inverted; }
    
private:
	bool m_loaded;
	std::string m_textureName;
	Box m_box; // only for texture coords
	Vector4 m_size;
    Vector4 m_pivot;
	Box m_boundingBox;
	Vector4 m_normal;
    bool m_inverted;
	Texture* m_texture;
	float m_verts[4 * 4];
	float m_coords[4 * 2];
	static const float DEFAULT_VERTS[4 * 4];
};