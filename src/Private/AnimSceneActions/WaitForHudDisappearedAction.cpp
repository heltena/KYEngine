#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/WaitForHudDisappearedAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string WaitForHudDisappearedAction::XML_NODE = "wait-for-hud-disappeared";

WaitForHudDisappearedAction::WaitForHudDisappearedAction()
{
}

WaitForHudDisappearedAction::~WaitForHudDisappearedAction()
{
}

WaitForHudDisappearedAction* WaitForHudDisappearedAction::readFromXml(TiXmlElement* node)
{
	WaitForHudDisappearedAction* action = new WaitForHudDisappearedAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void WaitForHudDisappearedAction::start(SceneTimelineInfo* info)
{
	m_isFinished = Core::hudManager().isPlayingHudDisappeared();
}

bool WaitForHudDisappearedAction::isBlocking()
{
	return  true;
}

bool WaitForHudDisappearedAction::isFinished()
{
	return  m_isFinished;
}

void WaitForHudDisappearedAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
	m_isFinished = Core::hudManager().isPlayingHudDisappeared();
}


