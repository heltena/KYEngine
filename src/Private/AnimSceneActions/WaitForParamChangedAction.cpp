#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/WaitForParamChangedAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string WaitForParamChangedAction::XML_NODE = "wait-for-param-changed";

WaitForParamChangedAction::WaitForParamChangedAction()
{
}

WaitForParamChangedAction::~WaitForParamChangedAction()
{
}

WaitForParamChangedAction* WaitForParamChangedAction::readFromXml(TiXmlElement* node)
{
	WaitForParamChangedAction* action = new WaitForParamChangedAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string paramRef = TiXmlHelper::readString(node, "param-ref", true);
	
	action->setName(name);
	action->setParamRef(paramRef);
	
	return action;
}

void WaitForParamChangedAction::start(SceneTimelineInfo* info)
{
	m_isFinished = false;
	info->waitForParamChanged(m_paramRef, this);
}

bool WaitForParamChangedAction::isBlocking()
{
	return true;
}

bool WaitForParamChangedAction::isFinished()
{
	return m_isFinished;
}

void WaitForParamChangedAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
