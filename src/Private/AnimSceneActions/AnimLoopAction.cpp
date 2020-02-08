#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/AnimLoopAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

const std::string AnimLoopAction::XML_NODE = "anim-loop";

AnimLoopAction::AnimLoopAction()
{
}

AnimLoopAction::~AnimLoopAction()
{
}

AnimLoopAction* AnimLoopAction::readFromXml(TiXmlElement* node)
{
	AnimLoopAction* action = new AnimLoopAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	const bool loop = TiXmlHelper::readBool(node, "loop", false, true);

	action->setName(name);
	action->setEntityRef(entityRef);
	action->setLoop(loop);

    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == "anim-point") {
            const std::string animRef = TiXmlHelper::readString(curr, "anim-ref", false, "<<undefined>>");
            action->addAnimRef(animRef);
			const double duration = TiXmlHelper::readDouble(curr, "duration", true);
			action->addDuration(duration);
        } else
			throw std::runtime_error("AnimLoopAction anim-point: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
            
	return action;
}

void AnimLoopAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
	m_elapsedTime = 0;
	m_curSegment = 0;
	m_entity->setAnim(m_animRefs[0]);
}

bool AnimLoopAction::isBlocking()
{
	return false;
}

bool AnimLoopAction::isFinished()
{
	return !m_loop && m_curSegment >= m_durations.size();
}

void AnimLoopAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
	m_elapsedTime += elapsedTime;
	bool needChangeAnim = false;

	while (m_curSegment < m_durations.size() && m_elapsedTime > m_durations[m_curSegment]) {
		m_elapsedTime -= m_durations[m_curSegment];
		if (m_loop)
			m_curSegment = (m_curSegment + 1) % m_durations.size();
		else
			m_curSegment++;
		needChangeAnim = true;
	}
	if (needChangeAnim && m_curSegment < m_durations.size())
		m_entity->setAnim(m_animRefs[m_curSegment]);

}
