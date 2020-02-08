#include <KYEngine/Private/AnimSceneActions/MapItemParam.h>

#include <KYEngine/Utility/TiXmlHelper.h>

const std::string MapItemParam::XML_NODE = "map-item";

MapItemParam::MapItemParam()
{
}

MapItemParam::MapItemParam(const MapItemParam& other)
    : m_id(other.m_id)
    , m_leftMeshRef(other.m_leftMeshRef)
    , m_rightMeshRef(other.m_rightMeshRef)
{
}

MapItemParam::~MapItemParam()
{
}

MapItemParam* MapItemParam::readFromXml(TiXmlElement* node)
{
    MapItemParam* result = new MapItemParam();
    
    const int id = TiXmlHelper::readInt(node, "id", true);
    const std::string& leftMeshRef = TiXmlHelper::readString(node, "left-mesh-ref", true);
    const std::string& rightMeshRef = TiXmlHelper::readString(node, "right-mesh-ref", true);
    
    result->setId(id);
    result->setLeftMeshRef(leftMeshRef);
    result->setRightMeshRef(rightMeshRef);
    
    return result;
}
