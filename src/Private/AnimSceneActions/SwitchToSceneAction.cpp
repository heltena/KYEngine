#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/SwitchToSceneAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string SwitchToSceneAction::XML_NODE = "switch-to-scene";

SwitchToSceneAction::SwitchToSceneAction()
{
}

SwitchToSceneAction::~SwitchToSceneAction()
{
}

SwitchToSceneAction* SwitchToSceneAction::readFromXml(TiXmlElement* node)
{
	SwitchToSceneAction* action = new SwitchToSceneAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string sceneRef = TiXmlHelper::readString(node, "scene-ref", true);
	const bool destroyStack = TiXmlHelper::readBool(node, "destroy-stack", false, true);
    
	action->setName(name);
	action->setSceneRef(sceneRef);
	action->setDestroyStack(destroyStack);
    
	return action;
}

void SwitchToSceneAction::start(SceneTimelineInfo* info)
{
	const std::string value = info->executeEL(m_sceneRef);
	Core::sceneManager().switchToScene(value, m_destroyStack);
}

bool SwitchToSceneAction::isBlocking()
{
	return false;
}

bool SwitchToSceneAction::isFinished()
{
	return true;
}

void SwitchToSceneAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
