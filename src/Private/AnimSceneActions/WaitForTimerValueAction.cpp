#include <KYEngine/Core.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTimerValueAction.h>

#include <iostream>

const std::string WaitForTimerValueAction::XML_NODE = "wait-for-timer-value";

WaitForTimerValueAction::WaitForTimerValueAction()
	: m_timerId(0)
{
}

WaitForTimerValueAction::~WaitForTimerValueAction()
{
}

WaitForTimerValueAction* WaitForTimerValueAction::readFromXml(TiXmlElement* node)
{
	WaitForTimerValueAction* action = new WaitForTimerValueAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string timerRef = TiXmlHelper::readString(node, "timer-ref", true);
    const double value = TiXmlHelper::readDouble(node, "value", true);
	
	action->setName(name);
    action->setTimerRef(timerRef);
    action->setValue(value);
	
	return action;
}

void WaitForTimerValueAction::start(SceneTimelineInfo* info)
{
    std::cout << "WaitForTimerValueAction::start " << m_name << std::endl;

    m_timerId = Core::timeManager().timer(m_timerRef);
#ifdef DEBUG
    std::cout << "WaitForTimerValueAction: timer '" << m_timerRef <<"' value = " << Core::timeManager().timerValue(m_timerId) << std::endl;
#endif
}

bool WaitForTimerValueAction::isBlocking()
{
	return true;
}

bool WaitForTimerValueAction::isFinished()
{
	return Core::timeManager().timerValue(m_timerId) >= m_value;
}

void WaitForTimerValueAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
