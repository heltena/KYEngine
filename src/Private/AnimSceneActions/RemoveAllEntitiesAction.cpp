#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllEntitiesAction.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string RemoveAllEntitiesAction::XML_NODE = "remove-all-entities";

RemoveAllEntitiesAction::RemoveAllEntitiesAction()
{
}

RemoveAllEntitiesAction::~RemoveAllEntitiesAction()
{
}

RemoveAllEntitiesAction* RemoveAllEntitiesAction::readFromXml(TiXmlElement* node)
{
	RemoveAllEntitiesAction* action = new RemoveAllEntitiesAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);

    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == "save-this") {
            const std::string entityRef = TiXmlHelper::readString(curr, "entity-ref", true);
            action->addSaveThisEntityRef(entityRef);
        } else
			throw std::runtime_error("RemoveAllEntitiesAction: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}

	return action;
}

void RemoveAllEntitiesAction::start(SceneTimelineInfo* info)
{
    if (m_saveTheseEntityRef.size() == 0)
        info->layer()->removeAllEntities();
    else {
        std::list<Entity*> saveThese;
        for(std::list<std::string>::const_iterator it = m_saveTheseEntityRef.begin(); it != m_saveTheseEntityRef.end(); it++) {
            Entity* entity = Core::resourceManager().entity(*it);
            saveThese.push_back(entity);
        }
        info->layer()->removeAllEntities(saveThese);
    }
}

bool RemoveAllEntitiesAction::isBlocking()
{
	return false;
}

bool RemoveAllEntitiesAction::isFinished()
{
	return true;
}

void RemoveAllEntitiesAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
