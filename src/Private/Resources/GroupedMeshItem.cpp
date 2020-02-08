#include <KYEngine/Core.h>
#include <KYEngine/Private/Resources/GroupedMeshItem.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string GroupedMeshItem::XML_NODE = "add-mesh";

GroupedMeshItem::GroupedMeshItem()
    : m_mesh(NULL)
{
}

GroupedMeshItem::~GroupedMeshItem()
{
    
}

GroupedMeshItem* GroupedMeshItem::readFromXml(TiXmlElement* node)
{
    GroupedMeshItem* result = new GroupedMeshItem();

    const std::string meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const Vector4 offset = TiXmlHelper::readVector(node, "ox", "oy", "oz", "", NO_READ, 0.0, 0.0, 0.0, 0.0);
    const Vector4 scale = TiXmlHelper::readVector(node, "sx", "sy", "sz", "", NO_READ, 1.0, 1.0, 1.0, 1.0);
    //const Vector4 color = TiXmlHelper::readVector(node, "r", "g", "b", "a", NO_READ, 1.0, 1.0, 1.0, 1.0);

    result->setMeshRef(meshRef);
    result->setOffset(offset);
    result->setScale(scale);
    //result->setColor(color);
    
    return result;
}

void GroupedMeshItem::load()
{
    m_mesh = Core::resourceManager().mesh(m_meshRef);
    m_boundingBox = m_mesh->boundingBox();
    m_boundingBox.scale(m_scale);
    m_boundingBox.translate(m_offset);
}

void GroupedMeshItem::unload()
{
    m_mesh = NULL;
}

void GroupedMeshItem::addMeshDataTo(OptimizedMeshData& meshData)
{
    OptimizedMeshData ownMeshData;
    m_mesh->addMeshDataTo(ownMeshData);
    ownMeshData.scale(m_scale);
    ownMeshData.translate(m_offset);
    meshData.addFullVertexData(ownMeshData);
}

void GroupedMeshItem::draw(double hpercent, int frame)
{
    glPushMatrix();
	glTranslatef(m_offset[0], m_offset[1], m_offset[2]);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    //glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
	m_mesh->draw(hpercent, frame);
	glPopMatrix();
}