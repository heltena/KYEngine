#include <KYEngine/Core.h>
#include <KYEngine/DialogInfo.h>
#include <KYEngine/Private/AnimSceneActions/ShowDialogPhraseParam.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string ShowDialogPhraseParam::XML_NODE = "phrase";

ShowDialogPhraseParam::ShowDialogPhraseParam()
{
}

ShowDialogPhraseParam::ShowDialogPhraseParam(const ShowDialogPhraseParam& other)
    : m_text(other.m_text)
    , m_color(other.m_color)
    , m_useTime(other.m_useTime)
    , m_time(other.m_time)
{
}

ShowDialogPhraseParam::~ShowDialogPhraseParam()
{
}

ShowDialogPhraseParam* ShowDialogPhraseParam::readFromXml(TiXmlElement* node)
{
    ShowDialogPhraseParam* result = new ShowDialogPhraseParam();
    const std::string text = TiXmlHelper::readString(node, "text", true);
    Vector4 color;
    if (TiXmlHelper::containsAttribute(node, "color-key")) {
        std::string colorKey = TiXmlHelper::readString(node, "color-key", true);
        color = Core::infoManager().dialogInfo().color(colorKey);
    } else 
        color = TiXmlHelper::readVector(node, "r", "g", "b", "", NO_READ, 1, 1, 1, 1);
    bool useTime = TiXmlHelper::containsAttribute(node, "time");
    double time = TiXmlHelper::readDouble(node, "time", false, 0);
    
    result->setText(text);
    result->setColor(color);
    result->setUseTime(useTime);
    result->setTime(time);
    
    return result;
}