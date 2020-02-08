#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Private/AnimSceneActions/UnlockMotionAction.h>

#include <stdexcept>

const std::string UnlockMotionAction::XML_NODE = "unlock-motion";

UnlockMotionAction::UnlockMotionAction()
{
}

UnlockMotionAction::~UnlockMotionAction()
{
}

UnlockMotionAction* UnlockMotionAction::readFromXml(TiXmlElement* element) {
	UnlockMotionAction* action = new UnlockMotionAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
	const std::string motionName = TiXmlHelper::readString(element, "motion-name", true);
    
	action->setName(name);
	action->setMotionName(motionName);
    
	return action;
}

void UnlockMotionAction::start(SceneTimelineInfo* info)
{
    Core::infoManager().unlockMotion(m_motionName);
}

bool UnlockMotionAction::isBlocking()
{
	return false;
}

bool UnlockMotionAction::isFinished()
{
	return true;
}

void UnlockMotionAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
