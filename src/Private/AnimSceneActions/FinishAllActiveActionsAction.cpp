#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/FinishAllActiveActionsAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string FinishAllActiveActionsAction::XML_NODE = "finish-all-active-actions";

FinishAllActiveActionsAction::FinishAllActiveActionsAction()
{
}

FinishAllActiveActionsAction::~FinishAllActiveActionsAction()
{
}

FinishAllActiveActionsAction* FinishAllActiveActionsAction::readFromXml(TiXmlElement* node)
{
	FinishAllActiveActionsAction* action = new FinishAllActiveActionsAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void FinishAllActiveActionsAction::start(SceneTimelineInfo* info)
{
	info->finishAllActiveActions();
}

bool FinishAllActiveActionsAction::isBlocking()
{
	return true;
}

bool FinishAllActiveActionsAction::isFinished()
{
	return true;
}

void FinishAllActiveActionsAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
