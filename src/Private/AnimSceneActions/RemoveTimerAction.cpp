#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/RemoveTimerAction.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string RemoveTimerAction::XML_NODE = "remove-timer";

RemoveTimerAction::RemoveTimerAction()
{
}

RemoveTimerAction::~RemoveTimerAction()
{
}

RemoveTimerAction* RemoveTimerAction::readFromXml(TiXmlElement* element) {
	RemoveTimerAction* action = new RemoveTimerAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
	const std::string timerRef = TiXmlHelper::readString(element, "timer-ref", true);

	action->setName(name);
	action->setTimerRef(timerRef);
	
	return action;
}

void RemoveTimerAction::start(SceneTimelineInfo* info)
{
    Core::timeManager().destroyTimer(m_timerRef);
}

bool RemoveTimerAction::isBlocking()
{
	return false;
}

bool RemoveTimerAction::isFinished()
{
	return true;
}

void RemoveTimerAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
