#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SetParamAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string SetParamAction::XML_NODE = "set-param";

SetParamAction::SetParamAction()
{
}

SetParamAction::~SetParamAction()
{
}

SetParamAction* SetParamAction::readFromXml(TiXmlElement* node)
{
	SetParamAction* action = new SetParamAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string paramRef = TiXmlHelper::readString(node, "param-ref", true);
	const std::string value = TiXmlHelper::readString(node, "value", true);
	
	action->setName(name);
	action->setParamRef(paramRef);
	action->setValue(value);
	
	return action;
}

void SetParamAction::start(SceneTimelineInfo* info)
{
	info->setParam(m_paramRef, info->executeEL(m_value));
}

bool SetParamAction::isBlocking()
{
	return false;
}

bool SetParamAction::isFinished()
{
	return true;
}

void SetParamAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
