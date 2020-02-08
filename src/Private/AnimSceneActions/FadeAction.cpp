#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/FadeAction.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>

const std::string FadeAction::XML_NODE = "fade";

FadeAction::FadeAction()
{
}

FadeAction::~FadeAction()
{
}

FadeAction* FadeAction::readFromXml(TiXmlElement* node)
{
	FadeAction* action = new FadeAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	double duration = TiXmlHelper::readDouble(node, "duration", true);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	bool fromCurrentAlpha = TiXmlHelper::readBool(node, "from-current-alpha", false, false);
	double from;
    if (! fromCurrentAlpha)
        from = TiXmlHelper::readDouble(node, "from", true);
	double to = TiXmlHelper::readDouble(node, "to", true);
    bool onlyAlpha = TiXmlHelper::readBool(node, "only-alpha", false, false);
	
	action->setName(name);
	action->setDuration(duration);
	action->setEntityRef(entityRef);
    action->setFromCurrentAlpha(fromCurrentAlpha);
	action->setFrom(from);
	action->setTo(to);
    action->setOnlyAlpha(onlyAlpha);
	
	return action;
}

void FadeAction::start(SceneTimelineInfo* info)
{
    if (m_entityRef == "#dark-background")
        m_entity = info->darkEntity();
    else
        m_entity = Core::resourceManager().entity(m_entityRef);
	Vector4 color = m_entity->color();
    if (m_fromCurrentAlpha)
        m_fromVector = color;
    else {
        m_fromVector = Vector4(color[0], color[1], color[2], m_from);
        m_entity->setColor(m_fromVector);
    }
	m_toVector = Vector4(color[0], color[1], color[2], m_to);
	m_elapsedTime = 0;
}

bool FadeAction::isBlocking()
{
	return false;
}

bool FadeAction::isFinished()
{
	return m_elapsedTime >= m_duration;
}

void FadeAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
	m_elapsedTime += elapsedTime;
	Vector4 newColor = Vector4::interpolate(m_fromVector, m_toVector, m_elapsedTime / m_duration);
    if (m_onlyAlpha)
        m_entity->color()[3] = newColor[3];
    else 
        m_entity->setColor(newColor);
}
