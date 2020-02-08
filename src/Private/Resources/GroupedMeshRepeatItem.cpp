#include <KYEngine/Core.h>
#include <KYEngine/Private/Resources/GroupedMeshRepeatItem.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string GroupedMeshRepeatItem::XML_NODE = "add-repeat-mesh";

GroupedMeshRepeatItem::GroupedMeshRepeatItem()
    : m_mesh(NULL)
{
}

GroupedMeshRepeatItem::~GroupedMeshRepeatItem()
{
    
}

GroupedMeshRepeatItem* GroupedMeshRepeatItem::readFromXml(TiXmlElement* node)
{
    GroupedMeshRepeatItem* result = new GroupedMeshRepeatItem();
    
    const std::string meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const Vector4 beginOffset = TiXmlHelper::readVector(node, "box", "boy", "boz", "", READ_X | READ_Y, 0.0, 0.0, 0.0, 0.0);
    const Vector4 scale = TiXmlHelper::readVector(node, "sx", "sy", "sz", "", NO_READ, 1.0, 1.0, 1.0, 0.0);
    const Vector4 stepOffset = TiXmlHelper::readVector(node, "stepx", "stepy", "stepz", "", READ_X | READ_Y, 1.0, 1.0, 1.0, 0.0);
    const int times = TiXmlHelper::readInt(node, "times", true);
    
    result->setMeshRef(meshRef);
    result->setBeginOffset(beginOffset);
    result->setScale(scale);
    result->setStepOffset(stepOffset);
    result->setTimes(times);
    
    return result;
}

void GroupedMeshRepeatItem::load()
{
    m_mesh = Core::resourceManager().mesh(m_meshRef);
    m_boundingBox = m_mesh->boundingBox();
    m_boundingBox.scale(m_scale);
    // TODO: esto no funciona!!!!
}

void GroupedMeshRepeatItem::unload()
{
    m_mesh = NULL;
}

void GroupedMeshRepeatItem::addMeshDataTo(OptimizedMeshData& meshData)
{
    Vector4 curTranslate = m_beginOffset;
    for(int i = 0; i < m_times; i++) {
        OptimizedMeshData ownData;
        m_mesh->addMeshDataTo(ownData);
        ownData.scale(m_scale);
        ownData.translate(curTranslate);
        meshData.addFullVertexData(ownData);
        
        curTranslate += m_stepOffset;
    }
}

void GroupedMeshRepeatItem::draw(double hpercent, int frame)
{
    glPushMatrix();
	glTranslatef(m_beginOffset[0], m_beginOffset[1], m_beginOffset[2]);
    for(int i = 0; i < m_times; i++) {
        glPushMatrix();
        glScalef(m_scale[0], m_scale[1], m_scale[2]);
        m_mesh->draw(hpercent, frame);
        glPopMatrix();
        glTranslatef(m_stepOffset[0], m_stepOffset[1], m_stepOffset[2]);
    }
	glPopMatrix();
}