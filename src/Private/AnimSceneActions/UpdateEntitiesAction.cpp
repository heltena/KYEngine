#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Private/AnimSceneActions/UpdateEntitiesAction.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

const std::string UpdateEntitiesAction::XML_NODE = "update-entities";

UpdateEntitiesAction::UpdateEntitiesAction()
{
}

UpdateEntitiesAction::~UpdateEntitiesAction()
{
}

UpdateEntitiesAction* UpdateEntitiesAction::readFromXml(TiXmlElement* node)
{
	UpdateEntitiesAction* action = new UpdateEntitiesAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");

	action->setName(name);

    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == "add-entity") {
            const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
            action->addAddEntityRef(entityRef);
        } else if (value == "remove-entity") {
            const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
            action->addRemoveEntityRef(entityRef);
        } else
			throw std::runtime_error("UpdateEntitiesAction: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
            
	return action;
}

void UpdateEntitiesAction::start(SceneTimelineInfo* info)
{
    std::list<Entity*> toAddEntities;
    std::list<Entity*> toRemoveEntities;
    
    for(std::list<std::string>::const_iterator it = m_toAddEntityRef.begin(); it != m_toAddEntityRef.end(); it++)
        toAddEntities.push_back(Core::resourceManager().entity(*it));
    for(std::list<std::string>::const_iterator it = m_toRemoveEntityRef.begin(); it != m_toRemoveEntityRef.end(); it++)
        toRemoveEntities.push_back(Core::resourceManager().entity(*it));

	info->layer()->updateEntities(toAddEntities, toRemoveEntities);
}

bool UpdateEntitiesAction::isBlocking()
{
	return false;
}

bool UpdateEntitiesAction::isFinished()
{
	return true;
}

void UpdateEntitiesAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
