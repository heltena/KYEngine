#pragma once

#include <tinyxml.h>

#include <KYEngine/Mesh.h>
#include <KYEngine/Optimizations/OptimizedMeshData.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class GroupedMeshItem
{
public:
    GroupedMeshItem();
    virtual ~GroupedMeshItem();
    
public:
	static const std::string XML_NODE;
	static GroupedMeshItem* readFromXml(TiXmlElement* node);

public:
    const std::string& meshRef() const { return m_meshRef; }
    const Vector4& offset() const { return m_offset; }
    const Box& boundingBox() const { return m_boundingBox; }
    
public:
    void load();
    void unload();
    void addMeshDataTo(OptimizedMeshData& meshData);
    void draw(double hpercent, int frame = 0);
    
public:
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setOffset(const Vector4& offset) { m_offset = offset; }
    void setScale(const Vector4& scale) { m_scale = scale; }
    //void setColor(const Vector4& color) { m_color = color; }
    
private:
    std::string m_meshRef;
    Vector4 m_offset;
    Vector4 m_scale;
    //Vector4 m_color;
    Mesh* m_mesh;
    Box m_boundingBox;
};