#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Private/AnimSceneActions/UnlockHelpAction.h>

#include <stdexcept>

const std::string UnlockHelpAction::XML_NODE = "unlock-help";

UnlockHelpAction::UnlockHelpAction()
{
}

UnlockHelpAction::~UnlockHelpAction()
{
}

UnlockHelpAction* UnlockHelpAction::readFromXml(TiXmlElement* element) {
	UnlockHelpAction* action = new UnlockHelpAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
	int helpLevel = TiXmlHelper::readInt(element, "help-level", true);
    
	action->setName(name);
	action->setHelpLevel(helpLevel);
    
	return action;
}

void UnlockHelpAction::start(SceneTimelineInfo* info)
{
    Core::infoManager().unlockHelp(m_helpLevel);
}

bool UnlockHelpAction::isBlocking()
{
	return false;
}

bool UnlockHelpAction::isFinished()
{
	return true;
}

void UnlockHelpAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
