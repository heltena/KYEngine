#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/RemoveParticleEmitterAction.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string RemoveParticleEmitterAction::XML_NODE = "remove-particle-emitter";

RemoveParticleEmitterAction::RemoveParticleEmitterAction()
{
}

RemoveParticleEmitterAction::~RemoveParticleEmitterAction()
{
}

RemoveParticleEmitterAction* RemoveParticleEmitterAction::readFromXml(TiXmlElement* node)
{
	RemoveParticleEmitterAction* action = new RemoveParticleEmitterAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string particleEmitterIdRef = TiXmlHelper::readString(node, "particle-emitter-id", true);
	
	action->setName(name);
	action->setParticleEmitterIdRef(particleEmitterIdRef);
	
	return action;
}

void RemoveParticleEmitterAction::start(SceneTimelineInfo* info)
{
    int particleEmitterId;
    std::string value = info->executeEL(m_particleEmitterIdRef);
    std::stringstream ss(value);
    ss >> particleEmitterId;

    Core::particleSystemManager().removeParticleEmitter(particleEmitterId);
}

bool RemoveParticleEmitterAction::isBlocking()
{
	return false;
}

bool RemoveParticleEmitterAction::isFinished()
{
	return true;
}

void RemoveParticleEmitterAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
