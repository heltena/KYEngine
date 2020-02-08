#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Utility/DirectionEnum.h>
#include <KYEngine/Utility/Vector4.h>

class ColoredRectangleMeshResource
	: public MeshResource
{
public:
	ColoredRectangleMeshResource();
	virtual ~ColoredRectangleMeshResource();
    
public:
	static const std::string XML_NODE;
	static ColoredRectangleMeshResource* readFromXml(TiXmlElement* node);
	
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
	void setSize(const Vector4& size);
	void setNormal(const Vector4& normal) { m_normal = normal; }
    void setPivot(const Vector4& pivot);
	
private:
	bool m_loaded;
	Vector4 m_size;
	Box m_boundingBox;
	Vector4 m_normal;
    Vector4 m_pivot;
	Texture* m_texture;
	float m_verts[4 * 4];
	static const float DEFAULT_VERTS[4 * 4];
};