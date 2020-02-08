#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Utility/DirectionEnum.h>
#include <KYEngine/Utility/Vector4.h>

class GradientRectangleMeshResource
	: public MeshResource
{
public:
	GradientRectangleMeshResource();
	virtual ~GradientRectangleMeshResource();
    
public:
	static const std::string XML_NODE;
	static GradientRectangleMeshResource* readFromXml(TiXmlElement* node);
	
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
    void setTopLeftColor(const Vector4& topLeftColor) { m_topLeftColor = topLeftColor; }
    void setTopRightColor(const Vector4& topRightColor) { m_topRightColor = topRightColor; }
    void setBottomLeftColor(const Vector4& bottomLeftColor) { m_bottomLeftColor = bottomLeftColor; }
    void setBottomRightColor(const Vector4& bottomRightColor) { m_bottomRightColor = bottomRightColor; }
	
private:
	bool m_loaded;
	Vector4 m_size;
	Box m_boundingBox;
	Vector4 m_normal;
    Vector4 m_pivot;
    Vector4 m_topLeftColor;
    Vector4 m_topRightColor;
    Vector4 m_bottomLeftColor;
    Vector4 m_bottomRightColor;
	Texture* m_texture;
	float m_verts[4 * 4];
    unsigned char m_colors[4 * 4];
	static const float DEFAULT_VERTS[4 * 4];
};