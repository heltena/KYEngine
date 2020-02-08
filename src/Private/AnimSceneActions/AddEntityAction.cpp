#include <KYEngine/Private/AnimSceneActions/AddEntityAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string AddEntityAction::XML_NODE = "add-entity";

AddEntityAction::AddEntityAction()
{
}

AddEntityAction::~AddEntityAction()
{
}

AddEntityAction* AddEntityAction::readFromXml(TiXmlElement* element) {
	AddEntityAction* action = new AddEntityAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(element, "entity-ref", true);
	const Vector4 initialPos = TiXmlHelper::readVector(element, "ix", "iy", "iz", "", READ_X | READ_Y | READ_Z);
	const Vector4 initialColor = TiXmlHelper::readVector(element, "ir", "ig", "ib", "ia", NO_READ, 1.0f, 1.0f, 1.0f, 1.0f);
    const Vector4 initialScale = TiXmlHelper::readVector(element, "sx", "sy", "sz", "", NO_READ, 1.0f, 1.0f, 1.0f, 1.0f);
    const double initialAngle = TiXmlHelper::readDouble(element, "angle", false, 0);
    const bool useAnimRef = TiXmlHelper::containsAttribute(element, "anim-ref");
    std::string animRef;
    if (useAnimRef)
        animRef = TiXmlHelper::readString(element, "anim-ref", true);
    const bool useUseBlending = TiXmlHelper::containsAttribute(element, "use-blending");
    bool useBlending = false;
    if (useUseBlending)
        useBlending = TiXmlHelper::readBool(element, "use-blending", true);
    
	action->setName(name);
	action->setEntityRef(entityRef);
	action->setInitialPos(initialPos);
	action->setInitialColor(initialColor);
    action->setInitialAngle(initialAngle);
    action->setInitialScale(initialScale);
    action->setUseAnimRef(useAnimRef);
    action->setAnimRef(animRef);
    action->setUseUseBlending(useUseBlending);
	action->setUseBlending(useBlending);

	return action;
}

void AddEntityAction::start(SceneTimelineInfo* info)
{
	Entity* entity = Core::resourceManager().entity(m_entityRef);
	entity->setPos(m_initialPos);
	entity->setColor(m_initialColor);
    entity->setAngle(m_initialAngle);
    entity->setScale(m_initialScale);
    if (m_useUseBlending)
        entity->setUseBlending(m_useBlending);
    if (m_useAnimRef)
        entity->setAnim(info->executeEL(m_animRef));
	info->layer()->addEntity(entity);
}

bool AddEntityAction::isBlocking()
{
	return false;
}

bool AddEntityAction::isFinished()
{
	return true;
}

void AddEntityAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
