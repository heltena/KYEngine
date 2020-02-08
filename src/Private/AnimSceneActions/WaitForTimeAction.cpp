#include <KYEngine/Private/AnimSceneActions/WaitForTimeAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string WaitForTimeAction::XML_NODE = "wait-for-time";

WaitForTimeAction::WaitForTimeAction()
	: m_time(0.0)
{
}

WaitForTimeAction::~WaitForTimeAction()
{
}

WaitForTimeAction* WaitForTimeAction::readFromXml(TiXmlElement* node)
{
	WaitForTimeAction* action = new WaitForTimeAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	double time = TiXmlHelper::readDouble(node, "time", true);
	
	action->setName(name);
	action->setTime(time);
	
	return action;
}

void WaitForTimeAction::start(SceneTimelineInfo* info)
{
	m_elapsedTime = 0.0f;
}

bool WaitForTimeAction::isBlocking()
{
	return true;
}

bool WaitForTimeAction::isFinished()
{
	return m_elapsedTime >= m_time;
}

void WaitForTimeAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
	m_elapsedTime += elapsedTime;
}
