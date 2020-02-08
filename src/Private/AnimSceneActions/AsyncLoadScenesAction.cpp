#include <KYEngine/Private/AnimSceneActions/AsyncLoadScenesAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string AsyncLoadScenesAction::XML_NODE = "async-load-scenes";

AsyncLoadScenesAction::AsyncLoadScenesAction()
{
}

AsyncLoadScenesAction::~AsyncLoadScenesAction()
{
    m_worker.join();
}

AsyncLoadScenesAction* AsyncLoadScenesAction::readFromXml(TiXmlElement* node)
{
	AsyncLoadScenesAction* action = new AsyncLoadScenesAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string filename = TiXmlHelper::readString(node, "filename", true);
    
	action->setName(name);
    action->setFilename(filename);

	return action;
}

void AsyncLoadScenesAction::start(SceneTimelineInfo* info)
{
    m_worker.run(this);
}

void AsyncLoadScenesAction::stop(SceneTimelineInfo* info)
{
    m_worker.join();
}

bool AsyncLoadScenesAction::isBlocking()
{
	return false;
}

bool AsyncLoadScenesAction::isFinished()
{
	return m_worker.isFinished();
}

void AsyncLoadScenesAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}

void* AsyncLoadScenesAction::workRun()
{
    Core::sceneManager().registerAnimScenes(m_filename);
    return NULL;
}