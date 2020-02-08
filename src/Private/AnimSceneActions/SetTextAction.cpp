#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SetTextAction.h>
#include <KYEngine/TextLayerExtension.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string SetTextAction::XML_NODE = "set-text";

SetTextAction::SetTextAction()
{
}

SetTextAction::~SetTextAction()
{
}

SetTextAction* SetTextAction::readFromXml(TiXmlElement* node)
{
	SetTextAction* action = new SetTextAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	const std::string text = TiXmlHelper::readString(node, "text", true);
	bool useLineLength = TiXmlHelper::containsAttribute(node, "line-length");
    double lineLength = TiXmlHelper::readDouble(node, "line-length", false, 0);
    bool useLineSpacing = TiXmlHelper::containsAttribute(node, "line-spacing");
    double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", false, 1);
    bool useAlignment = TiXmlHelper::containsAttribute(node, "align");
    AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_LEFT);
    
	action->setName(name);
	action->setEntityRef(entityRef);
	action->setText(text);
	action->setUseLineLength(useLineLength);
    action->setLineLength(lineLength);
    action->setUseLineSpacing(useLineSpacing);
    action->setLineSpacing(lineSpacing);
    action->setUseAlignment(useAlignment);
    action->setAlign(align);
    
	return action;
}

void SetTextAction::start(SceneTimelineInfo* info)
{
	Entity* entity = Core::resourceManager().entity(m_entityRef);
	const std::string value = info->executeEL(m_text);
    TextLayerExtension* extension = entity->textLayerInterface();
    if (extension != NULL) {
        extension->setText(value);
        if (m_useLineLength)
            extension->setLineLength(m_lineLength);
        if (m_useLineSpacing)
            extension->setLineSpacing(m_lineSpacing);
        if (m_useAlignment)
            extension->setAlign(m_align);
    }
}

bool SetTextAction::isBlocking()
{
	return false;
}

bool SetTextAction::isFinished()
{
	return true;
}

void SetTextAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
