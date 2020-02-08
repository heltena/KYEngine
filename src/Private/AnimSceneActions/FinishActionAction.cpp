#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/FinishActionAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string FinishActionAction::XML_NODE = "finish-action";

FinishActionAction::FinishActionAction()
{
}

FinishActionAction::~FinishActionAction()
{
}

FinishActionAction* FinishActionAction::readFromXml(TiXmlElement* node)
{
	FinishActionAction* action = new FinishActionAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string actionRef = TiXmlHelper::readString(node, "action-ref", true);
	
	action->setName(name);
	action->setActionRef(actionRef);
	
	return action;
}

void FinishActionAction::start(SceneTimelineInfo* info)
{
	info->finishAction(m_actionRef);
}

bool FinishActionAction::isBlocking()
{
	return true;
}

bool FinishActionAction::isFinished()
{
	return true;
}

void FinishActionAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
