#pragma once

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/GroupedMeshItem.h>

class GroupedMeshRepeatItem
{
public:
    GroupedMeshRepeatItem();
    virtual ~GroupedMeshRepeatItem();
    
public:
	static const std::string XML_NODE;
	static GroupedMeshRepeatItem* readFromXml(TiXmlElement* node);
    
public:
    const std::string& meshRef() const { return m_meshRef; }
    const Vector4& beginOffset() const { return m_beginOffset; }
    const Vector4& stepOffset() const { return m_stepOffset; }
    int times() const { return m_times; }
    const Box& boundingBox() const { return m_boundingBox; }
    
private:
    friend class GroupedMeshResource;
    void load();
    void unload();
    void addMeshDataTo(OptimizedMeshData& meshData);
    void draw(double hpercent, int frame = 0);
    
private:
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setBeginOffset(const Vector4& beginOffset) { m_beginOffset = beginOffset; }
    void setScale(const Vector4& scale) { m_scale = scale; }
    void setStepOffset(const Vector4& stepOffset) { m_stepOffset = stepOffset; }
    void setTimes(int times) { m_times = times; }
    
private:
    std::string m_meshRef;
    Vector4 m_beginOffset;
    Vector4 m_scale;
    Vector4 m_stepOffset;
    int m_times;
    Mesh* m_mesh;
    Box m_boundingBox;
};
