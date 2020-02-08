#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/PopSceneAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string PopSceneAction::XML_NODE = "pop-scene";

PopSceneAction::PopSceneAction()
{
}

PopSceneAction::~PopSceneAction()
{
}

PopSceneAction* PopSceneAction::readFromXml(TiXmlElement* node)
{
	PopSceneAction* action = new PopSceneAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void PopSceneAction::start(SceneTimelineInfo* info)
{
	Core::sceneManager().switchToPopedScene();
}

bool PopSceneAction::isBlocking()
{
	return false;
}

bool PopSceneAction::isFinished()
{
	return true;
}

void PopSceneAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
