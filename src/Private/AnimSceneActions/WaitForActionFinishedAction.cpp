#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/WaitForActionFinishedAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string WaitForActionFinishedAction::XML_NODE = "wait-for-action-finished";

WaitForActionFinishedAction::WaitForActionFinishedAction()
{
}

WaitForActionFinishedAction::~WaitForActionFinishedAction()
{
}

WaitForActionFinishedAction* WaitForActionFinishedAction::readFromXml(TiXmlElement* node)
{
	WaitForActionFinishedAction* action = new WaitForActionFinishedAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string actionRef = TiXmlHelper::readString(node, "action-ref", true);
	
	action->setName(name);
	action->setActionRef(actionRef);
	
	return action;
}

void WaitForActionFinishedAction::start(SceneTimelineInfo* info)
{
    if (info->isActionFinished(m_actionRef))
        m_isFinished = true;
    else {
        m_isFinished = false;
        info->waitForActionFinished(m_actionRef, this);
    }
}

bool WaitForActionFinishedAction::isBlocking()
{
	return true;
}

bool WaitForActionFinishedAction::isFinished()
{
	return m_isFinished;
}

void WaitForActionFinishedAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
