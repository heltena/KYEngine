#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllToggleButtonEventsAction.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string RemoveAllToggleButtonEventsAction::XML_NODE = "remove-all-toggle-button-events";

RemoveAllToggleButtonEventsAction::RemoveAllToggleButtonEventsAction()
{
}

RemoveAllToggleButtonEventsAction::~RemoveAllToggleButtonEventsAction()
{
}

RemoveAllToggleButtonEventsAction* RemoveAllToggleButtonEventsAction::readFromXml(TiXmlElement* node)
{
	RemoveAllToggleButtonEventsAction* action = new RemoveAllToggleButtonEventsAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void RemoveAllToggleButtonEventsAction::start(SceneTimelineInfo* info)
{
    info->removeAllToggleButtonEvents();
}

bool RemoveAllToggleButtonEventsAction::isBlocking()
{
	return false;
}

bool RemoveAllToggleButtonEventsAction::isFinished()
{
	return true;
}

void RemoveAllToggleButtonEventsAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
