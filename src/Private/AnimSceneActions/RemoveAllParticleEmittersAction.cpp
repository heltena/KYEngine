#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllParticleEmittersAction.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const std::string RemoveAllParticleEmittersAction::XML_NODE = "remove-all-particle-emitters";

RemoveAllParticleEmittersAction::RemoveAllParticleEmittersAction()
{
}

RemoveAllParticleEmittersAction::~RemoveAllParticleEmittersAction()
{
}

RemoveAllParticleEmittersAction* RemoveAllParticleEmittersAction::readFromXml(TiXmlElement* node)
{
	RemoveAllParticleEmittersAction* action = new RemoveAllParticleEmittersAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	
	action->setName(name);
	
	return action;
}

void RemoveAllParticleEmittersAction::start(SceneTimelineInfo* info)
{
    Core::particleSystemManager().removeAllParticleEmitters();
}

bool RemoveAllParticleEmittersAction::isBlocking()
{
	return false;
}

bool RemoveAllParticleEmittersAction::isFinished()
{
	return true;
}

void RemoveAllParticleEmittersAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
