#include <KYEngine/Private/Resources/AddTextLabelParamImpl.h>
#include <KYEngine/Core.h>

#include <KYEngine/Utility/TiXmlHelper.h>

const std::string AddTextLabelParamImpl::XML_NODE = "add-text-label";

AddTextLabelParamImpl::AddTextLabelParamImpl()
{
}

AddTextLabelParamImpl::AddTextLabelParamImpl(const AddTextLabelParamImpl& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_fontRef(other.m_fontRef)
    , m_defaultText(other.m_defaultText)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_color(other.m_color)
    , m_borderColor(other.m_borderColor)
    , m_lineLength(other.m_lineLength)
    , m_lineSpacing(other.m_lineSpacing)
    , m_align(other.m_align)
{
}

AddTextLabelParamImpl::~AddTextLabelParamImpl()
{
}

AddTextLabelParamImpl* AddTextLabelParamImpl::readFromXml(TiXmlElement* node)
{
    AddTextLabelParamImpl* result = new AddTextLabelParamImpl();
    
    const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const int id = TiXmlHelper::readInt(node, "id", true);
    const std::string& fontRef = TiXmlHelper::readString(node, "font-ref", true);
    const std::string& defaultText = TiXmlHelper::readString(node, "default-text", true);
    const Vector4 appearedPos = TiXmlHelper::readVector(node, "ax", "ay", "az", "", READ_X | READ_Y | READ_Z);
    const Vector4 disappearedPos = TiXmlHelper::readVector(node, "dx", "dy", "dz", "", READ_X | READ_Y | READ_Z);
    const double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", true);
    const Vector4 color = TiXmlHelper::readVector(node, "r", "g", "b", "a", NO_READ, 1, 1, 1, 1);
    const Vector4 borderColor = TiXmlHelper::readVector(node, "br", "bg", "bb", "ba", NO_READ, 0, 0, 0, 1);
    const double lineLength = TiXmlHelper::readDouble(node, "line-length", true);
    const double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", true);
    const AlignType align = TiXmlHelper::readAlignType(node, "align", true);
    
    result->setId(id);
    result->setName(name);
    result->setFontRef(fontRef);
    result->setDefaultText(defaultText);
    result->setAppearedPos(appearedPos);
    result->setDisappearedPos(disappearedPos);
    result->setAnimDuration(animDuration);
    result->setAccelMagnitude(accelMagnitude);
    result->setColor(color);
    result->setBorderColor(borderColor);
    result->setLineLength(lineLength);
    result->setLineSpacing(lineSpacing);
    result->setAlign(align);
    
    return result;
}

HudTextLabel* AddTextLabelParamImpl::generateTextLabel() const
{
    Font* font = Core::resourceManager().font(m_fontRef);
    return new HudTextLabel(m_id, m_name, m_appearedPos, m_disappearedPos, m_animDuration, m_accelMagnitude, font, m_defaultText, m_color, m_borderColor, m_lineLength, m_lineSpacing, m_align);
}