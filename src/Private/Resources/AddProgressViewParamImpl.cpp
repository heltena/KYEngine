#include <KYEngine/Private/Resources/AddProgressViewParamImpl.h>
#include <KYEngine/Core.h>

#include <KYEngine/Utility/TiXmlHelper.h>

const std::string AddProgressViewParamImpl::XML_NODE = "add-progress-view";

AddProgressViewParamImpl::AddProgressViewParamImpl()
{
}

AddProgressViewParamImpl::AddProgressViewParamImpl(const AddProgressViewParamImpl& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_backgroundMeshRef(other.m_backgroundMeshRef)
    , m_meshRef(other.m_meshRef)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_offset(other.m_offset)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_minValue(other.m_minValue)
    , m_maxValue(other.m_maxValue)
    , m_initialValue(other.m_initialValue)
    , m_ltr(other.m_ltr)
    , m_angle(other.m_angle)
{
}

AddProgressViewParamImpl::~AddProgressViewParamImpl()
{
}

AddProgressViewParamImpl* AddProgressViewParamImpl::readFromXml(TiXmlElement* node)
{
    AddProgressViewParamImpl* result = new AddProgressViewParamImpl();
    
    const int id = TiXmlHelper::readInt(node, "id", true);
    const std::string name = TiXmlHelper::readString(node, "name", false, "#UNDEF");
    const std::string& backgroundMeshRef = TiXmlHelper::readString(node, "background-mesh-ref", true);
    const std::string& meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
    const Vector4& appearedPos = TiXmlHelper::readVector(node, "ax", "ay", "az", "", READ_X | READ_Y | READ_Z);
    const Vector4& disappearedPos = TiXmlHelper::readVector(node, "dx", "dy", "dz", "", READ_X | READ_Y | READ_Z);
    const Vector4& offset = TiXmlHelper::readVector(node, "ox", "oy", "oz", "", NO_READ, 0, 0, 0, 0);
    const double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", true);
    const double minValue = TiXmlHelper::readDouble(node, "min-value", true);
    const double maxValue = TiXmlHelper::readDouble(node, "max-value", true);
    const double initialValue = TiXmlHelper::readDouble(node, "initial-value", true);
    const bool ltr = TiXmlHelper::readBool(node, "ltr", false, true);
    const double angle = TiXmlHelper::readDouble(node, "angle", false, 0);
    
    result->setId(id);
    result->setBackgroundMeshRef(backgroundMeshRef);
    result->setMeshRef(meshRef);
    result->setAppearedPos(appearedPos);
    result->setDisappearedPos(disappearedPos);
    result->setOffset(offset);
    result->setAnimDuration(animDuration);
    result->setAccelMagnitude(accelMagnitude);
    result->setMinValue(minValue);
    result->setMaxValue(maxValue);
    result->setInitialValue(initialValue);
    result->setLtr(ltr);
    result->setAngle(angle);
    
    return result;
}

HudProgressView* AddProgressViewParamImpl::generateProgressView() const
{
    Mesh* backgroundMesh = Core::resourceManager().mesh(m_backgroundMeshRef);
    Mesh* mesh = Core::resourceManager().mesh(m_meshRef);
    return new HudProgressView(m_id, m_name, m_appearedPos, m_disappearedPos, m_offset, m_animDuration, m_accelMagnitude, m_minValue, m_maxValue, m_initialValue, m_ltr, m_angle, backgroundMesh, mesh);
}
