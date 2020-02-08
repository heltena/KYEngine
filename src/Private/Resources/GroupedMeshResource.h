#pragma once

#include <tinyxml.h>

#include <KYEngine/Optimizations/OptimizedMeshData.h>
#include <KYEngine/Private/Resources/GroupedMeshItem.h>
#include <KYEngine/Private/Resources/GroupedMeshRepeatItem.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

#include <list>

class GroupedMeshResource
    : public MeshResource
{
public:
	GroupedMeshResource();
	virtual ~GroupedMeshResource();

public:
	static const std::string XML_NODE;
	static GroupedMeshResource* readFromXml(TiXmlElement* node);

// Resource implementation
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
    void setCanOptimize(bool canOptimize) { m_canOptimize = canOptimize; }
    void setOffset(const Vector4& offset) { m_offset = offset; }
    void addChild(const GroupedMeshItem& item);
    void addRepeatChild(const GroupedMeshRepeatItem& repeatItem);

protected:
    Vector4 m_offset;
    std::list<GroupedMeshItem> m_children;
    std::list<GroupedMeshRepeatItem> m_repeatChildren;
	Box m_boundingBox;
    bool m_canOptimize;
    OptimizedMeshData m_optimizedMeshData;
};


