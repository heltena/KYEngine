#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/PopMusicAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string PopMusicAction::XML_NODE = "pop-music";

PopMusicAction::PopMusicAction()
{
}

PopMusicAction::~PopMusicAction()
{
}

PopMusicAction* PopMusicAction::readFromXml(TiXmlElement* node)
{
	PopMusicAction* action = new PopMusicAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void PopMusicAction::start(SceneTimelineInfo* info)
{
	Core::soundManager().popMusic();
}

bool PopMusicAction::isBlocking()
{
	return false;
}

bool PopMusicAction::isFinished()
{
	return true;
}

void PopMusicAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
