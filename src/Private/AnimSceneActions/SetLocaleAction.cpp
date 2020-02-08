#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SetLocaleAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string SetLocaleAction::XML_NODE = "set-locale";

SetLocaleAction::SetLocaleAction()
{
}

SetLocaleAction::~SetLocaleAction()
{
}

SetLocaleAction* SetLocaleAction::readFromXml(TiXmlElement* node)
{
	SetLocaleAction* action = new SetLocaleAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string locale = TiXmlHelper::readString(node, "locale", true);
	
	action->setName(name);
	action->setLocale(locale);
	
	return action;
}

void SetLocaleAction::start(SceneTimelineInfo* info)
{
	const std::string value = info->executeEL(m_locale);
	LocaleType locale = stringToLocale(value);
	Core::i18nManager().setLocale(locale);
}

bool SetLocaleAction::isBlocking()
{
	return false;
}

bool SetLocaleAction::isFinished()
{
	return true;
}

void SetLocaleAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
