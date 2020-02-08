#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/ActionBlockedListener.h>

class AnimSceneFactory;

class FinishAllActiveActionsAction
	: public Action
{
public:
	FinishAllActiveActionsAction();
	virtual ~FinishAllActiveActionsAction();
	
public:
	static const std::string XML_NODE;
	static FinishAllActiveActionsAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

public:
	void setName(const std::string& name) { m_name = name; }

private:
	std::string m_name;
	std::string m_actionRef;
};