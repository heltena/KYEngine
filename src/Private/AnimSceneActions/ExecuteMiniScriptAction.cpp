#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/ExecuteMiniScriptAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string ExecuteMiniScriptAction::XML_NODE = "execute-mini-script";

ExecuteMiniScriptAction::ExecuteMiniScriptAction()
{
}

ExecuteMiniScriptAction::~ExecuteMiniScriptAction()
{
}

ExecuteMiniScriptAction* ExecuteMiniScriptAction::readFromXml(TiXmlElement* node)
{
	ExecuteMiniScriptAction* action = new ExecuteMiniScriptAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string script = TiXmlHelper::readString(node, "script", true);
    const std::string executeIf = TiXmlHelper::readString(node, "execute-if", false, "true");
    bool block = TiXmlHelper::readBool(node, "block", false, false);
	
	action->setName(name);
	action->setScript(script);
    action->setBlock(block);
    action->setExecuteIf(executeIf);
	
	return action;
}

void ExecuteMiniScriptAction::start(SceneTimelineInfo* info)
{
    const std::string result = info->executeEL(m_executeIf);
    if (result == "false") {
        m_finished = true;
        return;
    }

    const std::string script = info->executeEL(m_script);
	info->executeEL(script);
    m_finished = !m_block;
}

bool ExecuteMiniScriptAction::isBlocking()
{
	return m_block;
}

bool ExecuteMiniScriptAction::isFinished()
{
	return m_finished;
}

void ExecuteMiniScriptAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    m_finished = true;
}
