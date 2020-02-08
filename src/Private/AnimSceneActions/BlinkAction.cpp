#include <KYEngine/Private/AnimSceneActions/BlinkAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string BlinkAction::XML_NODE = "blink";

BlinkAction::BlinkAction()
{
}

BlinkAction::~BlinkAction()
{
}

BlinkAction* BlinkAction::readFromXml(TiXmlElement* node)
{
	BlinkAction* action = new BlinkAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    double amplitude = TiXmlHelper::readDouble(node, "amplitude", true);
    double frecuency = TiXmlHelper::readDouble(node, "frecuency", true);
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
	
	action->setName(name);
    action->setAmplitude(amplitude);
    action->setFrecuency(frecuency);
	action->setEntityRef(entityRef);
	
	return action;
}

void BlinkAction::start(SceneTimelineInfo* info)
{
	m_entity = Core::resourceManager().entity(m_entityRef);
    m_elapsedTime = 0;
}

bool BlinkAction::isBlocking()
{
	return false;
}

bool BlinkAction::isFinished()
{
	return false;
}

void BlinkAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    m_elapsedTime += elapsedTime;
    double scale = 1 + m_amplitude * Math::sin(2 * M_PI * m_frecuency * m_elapsedTime);
    m_entity->setScale(Vector4(scale, scale, 1, 1));
}
