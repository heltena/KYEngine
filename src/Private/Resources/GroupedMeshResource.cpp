#include <KYEngine/Private/Resources/GroupedMeshRepeatItem.h>
#include <KYEngine/Private/Resources/GroupedMeshResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>
#include <stdexcept>

const std::string GroupedMeshResource::XML_NODE = "grouped-mesh";

GroupedMeshResource* GroupedMeshResource::readFromXml(TiXmlElement* node)
{
    GroupedMeshResource* result = new GroupedMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
    const Vector4 offset = TiXmlHelper::readVector(node, "ox", "oy", "oz", "", NO_READ);
    const bool canOptimize = TiXmlHelper::readBool(node, "can-optimize", false, false);
    
	result->setName(name);
    result->setOffset(offset);
    result->setCanOptimize(canOptimize);
    
	TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
		if (value == GroupedMeshItem::XML_NODE) {
            // TODO: fix it
            GroupedMeshItem* newItem = GroupedMeshItem::readFromXml(curr);
			result->addChild(*newItem);
            delete(newItem);
		} else if (value == GroupedMeshRepeatItem::XML_NODE) {
            GroupedMeshRepeatItem* newItem = GroupedMeshRepeatItem::readFromXml(curr);
            result->addRepeatChild(*newItem);
            delete(newItem);
        } else
			throw std::runtime_error("loadGroupedMesh(" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}

    return result;
}

GroupedMeshResource::GroupedMeshResource()
{
}

GroupedMeshResource::~GroupedMeshResource()
{
}

void GroupedMeshResource::preload()
{
    // TODO: preload
}

void GroupedMeshResource::unloadFromPreloaded()
{
}

void GroupedMeshResource::load()
{
    m_boundingBox = Box();

    for(std::list<GroupedMeshItem>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        it->load();
        m_boundingBox.unionWith(it->boundingBox());
    }
    for(std::list<GroupedMeshRepeatItem>::iterator it = m_repeatChildren.begin(); it != m_repeatChildren.end(); it++) {
        it->load();
        m_boundingBox.unionWith(it->boundingBox());
    }
    m_optimizedMeshData.clear();
}

void GroupedMeshResource::unload()
{
    for(std::list<GroupedMeshItem>::iterator it = m_children.begin(); it != m_children.end(); it++)
        it->unload();
    for(std::list<GroupedMeshRepeatItem>::iterator it = m_repeatChildren.begin(); it != m_repeatChildren.end(); it++)
        it->unload();
    m_optimizedMeshData.clear();
}

void GroupedMeshResource::draw(double hpercent, int frame)
{
    if (m_canOptimize) {
        if (! m_optimizedMeshData.optimized()) {
            m_optimizedMeshData.prepareData(NULL);
            for(std::list<GroupedMeshItem>::iterator it = m_children.begin(); it != m_children.end(); it++)
                it->addMeshDataTo(m_optimizedMeshData);
            for(std::list<GroupedMeshRepeatItem>::iterator it = m_repeatChildren.begin(); it != m_repeatChildren.end(); it++)
                it->addMeshDataTo(m_optimizedMeshData);
            m_optimizedMeshData.translate(m_offset);
            m_optimizedMeshData.optimize();
        }
        m_optimizedMeshData.draw();
    } else {
        glPushMatrix();
        glTranslatef(m_offset[0], m_offset[1], m_offset[2]);
        for(std::list<GroupedMeshItem>::iterator it = m_children.begin(); it != m_children.end(); it++)
            it->draw(hpercent, frame);
        for(std::list<GroupedMeshRepeatItem>::iterator it = m_repeatChildren.begin(); it != m_repeatChildren.end(); it++)
            it->draw(hpercent, frame);
        glPopMatrix();
    }
}

void GroupedMeshResource::addChild(const GroupedMeshItem& item)
{
    m_children.push_back(item);
}

void GroupedMeshResource::addRepeatChild(const GroupedMeshRepeatItem& repeatItem)
{
    m_repeatChildren.push_back(repeatItem);
}

void GroupedMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    if (! m_optimizedMeshData.optimized()) {
        m_optimizedMeshData.prepareData(NULL);
        for(std::list<GroupedMeshItem>::iterator it = m_children.begin(); it != m_children.end(); it++)
            it->addMeshDataTo(m_optimizedMeshData);
        for(std::list<GroupedMeshRepeatItem>::iterator it = m_repeatChildren.begin(); it !=     m_repeatChildren.end(); it++)
            it->addMeshDataTo(m_optimizedMeshData);
        m_optimizedMeshData.translate(m_offset);
    }
        
    data.addFullVertexData(m_optimizedMeshData);
}

