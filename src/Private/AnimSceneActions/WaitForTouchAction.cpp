#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTouchAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string WaitForTouchAction::XML_NODE = "wait-for-touch";

WaitForTouchAction::WaitForTouchAction()
{
}

WaitForTouchAction::~WaitForTouchAction()
{
}

WaitForTouchAction* WaitForTouchAction::readFromXml(TiXmlElement* node)
{
	WaitForTouchAction* action = new WaitForTouchAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void WaitForTouchAction::start(SceneTimelineInfo* info)
{
	m_isFinished = false;
	info->waitForGlobalTouch(this);
}

bool WaitForTouchAction::isBlocking()
{
	return  true;
}

bool WaitForTouchAction::isFinished()
{
	return  m_isFinished;
}

void WaitForTouchAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}


