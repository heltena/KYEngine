#include <KYEngine/Private/AnimSceneActions/AsyncLoadResourcesAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string AsyncLoadResourcesAction::XML_NODE = "async-load-resources";

AsyncLoadResourcesAction::AsyncLoadResourcesAction()
{
}

AsyncLoadResourcesAction::~AsyncLoadResourcesAction()
{
    m_worker.join();
}

AsyncLoadResourcesAction* AsyncLoadResourcesAction::readFromXml(TiXmlElement* node)
{
	AsyncLoadResourcesAction* action = new AsyncLoadResourcesAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string filename = TiXmlHelper::readString(node, "filename", true);
    
	action->setName(name);
    action->setFilename(filename);

	return action;
}

void AsyncLoadResourcesAction::start(SceneTimelineInfo* info)
{
    m_worker.run(this);
}

void AsyncLoadResourcesAction::stop(SceneTimelineInfo* info)
{
    m_worker.join();
}

bool AsyncLoadResourcesAction::isBlocking()
{
	return false;
}

bool AsyncLoadResourcesAction::isFinished()
{
	return m_worker.isFinished();
}

void AsyncLoadResourcesAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}

void* AsyncLoadResourcesAction::workRun()
{
    Core::resourceManager().loadResources(m_filename);
    return NULL;
}