#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/AddTextEntityAction.h>
#include <KYEngine/TextLayerExtension.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string AddTextEntityAction::XML_NODE = "add-text-entity";

AddTextEntityAction::AddTextEntityAction()
{
}

AddTextEntityAction::~AddTextEntityAction()
{
}

AddTextEntityAction* AddTextEntityAction::readFromXml(TiXmlElement* node)
{
	AddTextEntityAction* action = new AddTextEntityAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", READ_X | READ_Y | READ_Z);
	const Vector4 initialColor = TiXmlHelper::readVector(node, "ir", "ig", "ib", "ia", NO_READ, 1.0f, 1.0f, 1.0f, 1.0f);
    const Vector4 initialScale = TiXmlHelper::readVector(node, "sx", "sy", "sz", "", NO_READ, 1.0f, 1.0f, 1.0f, 1.0f);
    const double initialAngle = TiXmlHelper::readDouble(node, "angle", false, 0);
	const std::string text = TiXmlHelper::readString(node, "text", true);
    bool usePivot = TiXmlHelper::containsAttribute(node, "px") || TiXmlHelper::containsAttribute(node, "py");
    const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0, 0, 0, 0);
	bool useLineLength = TiXmlHelper::containsAttribute(node, "line-length");
    double lineLength = TiXmlHelper::readDouble(node, "line-length", false, 0);
    bool useLineSpacing = TiXmlHelper::containsAttribute(node, "line-spacing");
    double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", false, 1);
    bool useAlignment = TiXmlHelper::containsAttribute(node, "align");
    AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_LEFT);
    const bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
    
	action->setName(name);
	action->setEntityRef(entityRef);
	action->setInitialPos(initialPos);
	action->setInitialColor(initialColor);
    action->setInitialAngle(initialAngle);
    action->setInitialScale(initialScale);
	action->setText(text);
    action->setUsePivot(usePivot);
    action->setPivot(pivot);
	action->setUseLineLength(useLineLength);
    action->setLineLength(lineLength);
    action->setUseLineSpacing(useLineSpacing);
    action->setLineSpacing(lineSpacing);
    action->setUseAlignment(useAlignment);
    action->setAlign(align);
	action->setUseBlending(useBlending);
    
	return action;
}

void AddTextEntityAction::start(SceneTimelineInfo* info)
{
	Entity* entity = Core::resourceManager().entity(m_entityRef);
    
    TextLayerExtension* extension = entity->textLayerInterface();
    if (extension == NULL)
        throw std::runtime_error("Entity " + m_entityRef + " doesn't implement TextLayerExtension");
    
    const std::string value = info->executeEL(m_text);
    extension->setText(value);
    if (m_usePivot)
        extension->setPivot(m_pivot);
    if (m_useLineLength)
        extension->setLineLength(m_lineLength);
    if (m_useLineSpacing)
        extension->setLineSpacing(m_lineSpacing);
    if (m_useAlignment)
        extension->setAlign(m_align);
    
	entity->setPos(m_initialPos);
	entity->setColor(m_initialColor);
    entity->setAngle(m_initialAngle);
    entity->setScale(m_initialScale);
    entity->setUseBlending(m_useBlending);
	info->layer()->addEntity(entity);
}

bool AddTextEntityAction::isBlocking()
{
	return false;
}

bool AddTextEntityAction::isFinished()
{
	return true;
}

void AddTextEntityAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
