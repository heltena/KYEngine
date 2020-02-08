#include <KYEngine/Private/Resources/AddPushButtonParamImpl.h>
#include <KYEngine/Core.h>

#include <KYEngine/Utility/TiXmlHelper.h>

const std::string AddPushButtonParamImpl::XML_NODE = "add-push-button";

AddPushButtonParamImpl::AddPushButtonParamImpl()
{
}

AddPushButtonParamImpl::AddPushButtonParamImpl(const AddPushButtonParamImpl& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_meshRef(other.m_meshRef)
    , m_overMeshRef(other.m_overMeshRef)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_radius(other.m_radius)
{
}

AddPushButtonParamImpl::~AddPushButtonParamImpl()
{
}

AddPushButtonParamImpl* AddPushButtonParamImpl::readFromXml(TiXmlElement* node)
{
    AddPushButtonParamImpl* result = new AddPushButtonParamImpl();
    
    const int id = TiXmlHelper::readInt(node, "id", true);
    const std::string name = TiXmlHelper::readString(node, "name", false, "#UNDEF");
    const std::string& meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const std::string& overMeshRef = TiXmlHelper::readString(node, "over-mesh-ref", true);
    const Vector4& appearedPos = TiXmlHelper::readVector(node, "ax", "ay", "az", "", READ_X | READ_Y | READ_Z);
    const Vector4& disappearedPos = TiXmlHelper::readVector(node, "dx", "dy", "dz", "", READ_X | READ_Y | READ_Z);
    const double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", true);
    const double radius = TiXmlHelper::readDouble(node, "radius", true);
    
    result->setId(id);
    result->setMeshRef(meshRef);
    result->setOverMeshRef(overMeshRef);
    result->setAppearedPos(appearedPos);
    result->setDisappearedPos(disappearedPos);
    result->setAnimDuration(animDuration);
    result->setAccelMagnitude(accelMagnitude);
    result->setRadius(radius);

    return result;
}

HudPushButton* AddPushButtonParamImpl::generatePushButton() const
{
    Mesh* mesh = Core::resourceManager().mesh(m_meshRef);
    Mesh* overMesh = Core::resourceManager().mesh(m_overMeshRef);
    return new HudPushButton(m_id, m_name, m_appearedPos, m_disappearedPos, m_animDuration, m_accelMagnitude, m_radius, mesh, overMesh);
}
