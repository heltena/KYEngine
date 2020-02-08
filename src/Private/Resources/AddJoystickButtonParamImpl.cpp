#include <KYEngine/Private/Resources/AddJoystickButtonParamImpl.h>
#include <KYEngine/Core.h>

#include <KYEngine/Utility/TiXmlHelper.h>

const std::string AddJoystickButtonParamImpl::XML_NODE = "add-joystick-button";

AddJoystickButtonParamImpl::AddJoystickButtonParamImpl()
{
}

AddJoystickButtonParamImpl::AddJoystickButtonParamImpl(const AddJoystickButtonParamImpl& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_meshRef(other.m_meshRef)
    , m_backgroundMeshRef(other.m_backgroundMeshRef)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_radius(other.m_radius)
    , m_canMoveHorz(other.m_canMoveHorz)
    , m_canMoveVert(other.m_canMoveVert)
{
}

AddJoystickButtonParamImpl::~AddJoystickButtonParamImpl()
{
}

AddJoystickButtonParamImpl* AddJoystickButtonParamImpl::readFromXml(TiXmlElement* node)
{
    AddJoystickButtonParamImpl* result = new AddJoystickButtonParamImpl();
    
    const int id = TiXmlHelper::readInt(node, "id", true);
    const std::string name = TiXmlHelper::readString(node, "name", false, "#UNDEF");
    const std::string& meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const std::string& backgroundMeshRef = TiXmlHelper::readString(node, "background-mesh-ref", true);
    const Vector4& appearedPos = TiXmlHelper::readVector(node, "ax", "ay", "az", "", READ_X | READ_Y | READ_Z);
    const Vector4& disappearedPos = TiXmlHelper::readVector(node, "dx", "dy", "dz", "", READ_X | READ_Y | READ_Z);
    const double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", true);
    const double radius = TiXmlHelper::readDouble(node, "radius", true);
    const bool canMoveHorz = TiXmlHelper::readBool(node, "can-move-horz", false, true);
    const bool canMoveVert = TiXmlHelper::readBool(node, "can-move-vert", false, true);
    
    result->setId(id);
    result->setMeshRef(meshRef);
    result->setBackgroundMeshRef(backgroundMeshRef);
    result->setAppearedPos(appearedPos);
    result->setDisappearedPos(disappearedPos);
    result->setAnimDuration(animDuration);
    result->setAccelMagnitude(accelMagnitude);
    result->setRadius(radius);
    result->setCanMoveHorz(canMoveHorz);
    result->setCanMoveVert(canMoveVert);
    return result;
}

HudJoystickButton* AddJoystickButtonParamImpl::generateJoystickButton() const
{
    Mesh* mesh = Core::resourceManager().mesh(m_meshRef);
    Mesh* backgroundMesh = Core::resourceManager().mesh(m_backgroundMeshRef);
    return new HudJoystickButton(m_id, m_name, m_appearedPos, m_disappearedPos, m_animDuration, m_accelMagnitude, m_radius, mesh, backgroundMesh, m_canMoveHorz, m_canMoveVert);
}
