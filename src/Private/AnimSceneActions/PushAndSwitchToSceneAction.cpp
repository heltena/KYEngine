#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/PushAndSwitchToSceneAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string PushAndSwitchToSceneAction::XML_NODE = "push-and-switch-to-scene";

PushAndSwitchToSceneAction::PushAndSwitchToSceneAction()
{
}

PushAndSwitchToSceneAction::~PushAndSwitchToSceneAction()
{
}

PushAndSwitchToSceneAction* PushAndSwitchToSceneAction::readFromXml(TiXmlElement* node)
{
	PushAndSwitchToSceneAction* action = new PushAndSwitchToSceneAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string sceneRef = TiXmlHelper::readString(node, "scene-ref", true);
	const std::string executeIf = TiXmlHelper::readString(node, "execute-if", false, "true");
    
	action->setName(name);
	action->setSceneRef(sceneRef);
	action->setExecuteIf(executeIf);
    
	return action;
}

void PushAndSwitchToSceneAction::start(SceneTimelineInfo* info)
{
    const std::string result = info->executeEL(m_executeIf);
    if (result != "true")
        return;

	const std::string value = info->executeEL(m_sceneRef);
	Core::sceneManager().pushAndSwitchToScene(value);
}

bool PushAndSwitchToSceneAction::isBlocking()
{
	return false;
}

bool PushAndSwitchToSceneAction::isFinished()
{
	return true;
}

void PushAndSwitchToSceneAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
