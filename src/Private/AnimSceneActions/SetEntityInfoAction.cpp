#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/SetEntityInfoAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string SetEntityInfoAction::XML_NODE = "set-entity-info";

SetEntityInfoAction::SetEntityInfoAction()
{
}

SetEntityInfoAction::~SetEntityInfoAction()
{
}

SetEntityInfoAction* SetEntityInfoAction::readFromXml(TiXmlElement* node)
{
	SetEntityInfoAction* action = new SetEntityInfoAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    bool useAnimRef = TiXmlHelper::containsAttribute(node, "anim-ref");
    const std::string animRef = TiXmlHelper::readString(node, "anim-ref", false);
    bool useX = TiXmlHelper::containsAttribute(node, "x");
    bool useY = TiXmlHelper::containsAttribute(node, "y");
    bool useZ = TiXmlHelper::containsAttribute(node, "z");
    int mask = (useX ? READ_X : 0) | (useY ? READ_Y : 0) | (useZ ? READ_Z : 0);
    Vector4 newPos = TiXmlHelper::readVector(node, "x", "y", "z", "", mask);
    
	action->setName(name);
	action->setEntityRef(entityRef);
    action->setUseAnimRef(useAnimRef);
    action->setAnimRef(animRef);
	action->setUseX(useX);
	action->setUseY(useY);
	action->setUseZ(useZ);
    action->setNewPos(newPos);
    
	return action;
}

void SetEntityInfoAction::start(SceneTimelineInfo* info)
{
	Entity* entity = Core::resourceManager().entity(m_entityRef);
    
    if (m_useAnimRef)
        entity->setAnim(m_animRef);

    Vector4 pos = entity->pos();
    if (m_useX) pos[0] = m_newPos[0];
    if (m_useY) pos[1] = m_newPos[1];
    if (m_useZ) pos[2] = m_newPos[2];
    entity->setPos(pos);
}

bool SetEntityInfoAction::isBlocking()
{
	return false;
}

bool SetEntityInfoAction::isFinished()
{
	return true;
}

void SetEntityInfoAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
