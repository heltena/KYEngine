#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/CreateTimerAction.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string CreateTimerAction::XML_NODE = "create-timer";

CreateTimerAction::CreateTimerAction()
{
}

CreateTimerAction::~CreateTimerAction()
{
}

CreateTimerAction* CreateTimerAction::readFromXml(TiXmlElement* element) {
	CreateTimerAction* action = new CreateTimerAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
	const std::string timerName = TiXmlHelper::readString(element, "timer-name", true);

	action->setName(name);
	action->setTimerName(timerName);
	
	return action;
}

void CreateTimerAction::start(SceneTimelineInfo* info)
{
    Core::timeManager().createTimer(m_timerName);
}

bool CreateTimerAction::isBlocking()
{
	return false;
}

bool CreateTimerAction::isFinished()
{
	return true;
}

void CreateTimerAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
