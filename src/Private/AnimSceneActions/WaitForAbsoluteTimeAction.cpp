#include <KYEngine/Private/AnimSceneActions/WaitForAbsoluteTimeAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/SceneTimelineInfo.h>

const std::string WaitForAbsoluteTimeAction::XML_NODE = "wait-for-absolute-time";

WaitForAbsoluteTimeAction::WaitForAbsoluteTimeAction()
	: m_absoluteTime(0.0)
{
}

WaitForAbsoluteTimeAction::~WaitForAbsoluteTimeAction()
{
}

WaitForAbsoluteTimeAction* WaitForAbsoluteTimeAction::readFromXml(TiXmlElement* node)
{
	WaitForAbsoluteTimeAction* action = new WaitForAbsoluteTimeAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	double absoluteTime = TiXmlHelper::readDouble(node, "absolute-time", true);
	
	action->setName(name);
	action->setAbsoluteTime(absoluteTime);
	
	return action;
}

void WaitForAbsoluteTimeAction::start(SceneTimelineInfo* info)
{
    m_finished = false;
}

bool WaitForAbsoluteTimeAction::isBlocking()
{
	return true;
}

bool WaitForAbsoluteTimeAction::isFinished()
{
	return m_finished;
}

void WaitForAbsoluteTimeAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    m_finished = info->sceneElapsedTime() > m_absoluteTime;
}
