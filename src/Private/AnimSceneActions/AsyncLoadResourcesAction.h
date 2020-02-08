#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/AsyncWorker.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>
#include <KYEngine/Work.h>

#include <string>

class AnimSceneFactory;

class AsyncLoadResourcesAction
	: public Action
    , public Work
{
public:
	AsyncLoadResourcesAction();
	virtual ~AsyncLoadResourcesAction();

public:
	static const std::string XML_NODE;
	static AsyncLoadResourcesAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info);
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

// Work implementation
public:
    void* workRun();
    
public:
	void setName(const std::string& name) { m_name = name; }
    void setFilename(const std::string& filename) { m_filename = filename; }
    
private:
	std::string m_name;
    std::string m_filename;
    AsyncWorker m_worker;
};