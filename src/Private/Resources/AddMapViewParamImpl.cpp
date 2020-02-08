#include <KYEngine/Private/Resources/AddMapViewParamImpl.h>
#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/MapItemParam.h>

#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

const std::string AddMapViewParamImpl::XML_NODE = "add-map-view";

AddMapViewParamImpl::AddMapViewParamImpl()
{
}

AddMapViewParamImpl::AddMapViewParamImpl(const AddMapViewParamImpl& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_backgroundMeshRef(other.m_backgroundMeshRef)
    , m_meshRef(other.m_meshRef)
    , m_hasCenterMeshRef(other.m_hasCenterMeshRef)
    , m_centerMeshRef(other.m_centerMeshRef)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_offset(other.m_offset)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_width(other.m_width)
    , m_minValue(other.m_minValue)
    , m_maxValue(other.m_maxValue)
    , m_items(other.m_items)
{
}

AddMapViewParamImpl::~AddMapViewParamImpl()
{
}

AddMapViewParamImpl* AddMapViewParamImpl::readFromXml(TiXmlElement* node)
{
    AddMapViewParamImpl* result = new AddMapViewParamImpl();
    
    const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const int id = TiXmlHelper::readInt(node, "id", true);
    const std::string& backgroundMeshRef = TiXmlHelper::readString(node, "background-mesh-ref", true);
    const std::string& meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const bool hasCenterMeshRef = TiXmlHelper::containsAttribute(node, "center-mesh-ref");
    const std::string centerMeshRef = TiXmlHelper::readString(node, "center-mesh-ref", false);
    const Vector4& appearedPos = TiXmlHelper::readVector(node, "ax", "ay", "az", "", READ_X | READ_Y | READ_Z);
    const Vector4& disappearedPos = TiXmlHelper::readVector(node, "dx", "dy", "dz", "", READ_X | READ_Y | READ_Z);
    const Vector4& offset = TiXmlHelper::readVector(node, "ox", "oy", "oz", "", NO_READ, 0, 0, 0, 0);
    const double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", true);
    const double width = TiXmlHelper::readDouble(node, "width", true);
    const double minValue = TiXmlHelper::readDouble(node, "min-value", true);
    const double maxValue = TiXmlHelper::readDouble(node, "max-value", true);
    
    result->setName(name);
    result->setId(id);
    result->setBackgroundMeshRef(backgroundMeshRef);
    result->setMeshRef(meshRef);
    result->setHasCenterMeshRef(hasCenterMeshRef);
    result->setCenterMeshRef(centerMeshRef);
    result->setAppearedPos(appearedPos);
    result->setDisappearedPos(disappearedPos);
    result->setOffset(offset);
    result->setAnimDuration(animDuration);
    result->setAccelMagnitude(accelMagnitude);
    result->setWidth(width);
    result->setMinValue(minValue);
    result->setMaxValue(maxValue);
    
    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == MapItemParam::XML_NODE) {
            MapItemParam* param = MapItemParam::readFromXml(curr);
            result->addMapItem(*param);
            delete param;
		} else 
			throw std::runtime_error("AddMapViewParam tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
    
    return result;
}

HudMapView* AddMapViewParamImpl::generateMapView() const
{
    Mesh* backgroundMesh = Core::resourceManager().mesh(m_backgroundMeshRef);
    Mesh* mesh = Core::resourceManager().mesh(m_meshRef);
    Mesh* centerMesh = m_hasCenterMeshRef ? Core::resourceManager().mesh(m_centerMeshRef) : NULL;
    HudMapView* result = new HudMapView(m_id, m_name, m_appearedPos, m_disappearedPos, m_offset, m_animDuration, m_accelMagnitude, m_width, m_minValue, m_maxValue, backgroundMesh, mesh, centerMesh);
    for(std::map<int, MapItemParam>::const_iterator it = m_items.begin(); it != m_items.end(); it++) {
        Mesh* leftMesh = Core::resourceManager().mesh(it->second.leftMeshRef());
        Mesh* rightMesh = Core::resourceManager().mesh(it->second.rightMeshRef());
        result->addItemType(it->first, leftMesh, rightMesh);
    }
    return result;
}
