#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllTouchEventsAction.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string RemoveAllTouchEventsAction::XML_NODE = "remove-all-touch-events";

RemoveAllTouchEventsAction::RemoveAllTouchEventsAction()
{
}

RemoveAllTouchEventsAction::~RemoveAllTouchEventsAction()
{
}

RemoveAllTouchEventsAction* RemoveAllTouchEventsAction::readFromXml(TiXmlElement* node)
{
	RemoveAllTouchEventsAction* action = new RemoveAllTouchEventsAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void RemoveAllTouchEventsAction::start(SceneTimelineInfo* info)
{
    info->removeAllTouchEvents();
}

bool RemoveAllTouchEventsAction::isBlocking()
{
	return false;
}

bool RemoveAllTouchEventsAction::isFinished()
{
	return true;
}

void RemoveAllTouchEventsAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
