#include <KYEngine/Private/AnimSceneActions/AddNewParticleEmitterAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Sound.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <sstream>

const double AddNewParticleEmitterAction::TOUCH_TIMEOUT = 0.75;
const std::string AddNewParticleEmitterAction::XML_NODE = "add-new-particle-emitter";

AddNewParticleEmitterAction::AddNewParticleEmitterAction()
{
}

AddNewParticleEmitterAction::~AddNewParticleEmitterAction()
{
}

AddNewParticleEmitterAction* AddNewParticleEmitterAction::readFromXml(TiXmlElement* node)
{
	AddNewParticleEmitterAction* action = new AddNewParticleEmitterAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", NO_READ);
	const std::string particleEmitterRef = TiXmlHelper::readString(node, "particle-emitter-ref", true);
    bool hasTimeout = TiXmlHelper::containsAttribute(node, "timeout");
    double timeout = 0;
    if (hasTimeout)
        timeout = TiXmlHelper::readDouble(node, "timeout", false, 0);
    bool hasFollowEntityRef = TiXmlHelper::containsAttribute(node, "follow-entity-ref");
    std::string followEntityRef = "";
    if (hasFollowEntityRef)
        followEntityRef = TiXmlHelper::readString(node, "follow-entity-ref", true);
    const Vector4 followOffset = TiXmlHelper::readVector(node, "fex", "fey", "fez", "", NO_READ);
    const std::string setIdAtParamName = TiXmlHelper::readString(node, "set-id-at-param-name", false, "");
    const std::string executeIf = TiXmlHelper::readString(node, "execute-if", false, "true");
    
	action->setName(name);
    action->setInitialPos(initialPos);
    action->setParticleEmitterRef(particleEmitterRef);
    action->setHasTimeout(hasTimeout);
    action->setTimeout(timeout);
    action->setHasFollowEntityRef(hasFollowEntityRef);
    action->setFollowEntityRef(followEntityRef);
    action->setFollowOffset(followOffset);
    action->setSetIdAtParamName(setIdAtParamName);
    action->setExecuteIf(executeIf);
    
	return action;
}

void AddNewParticleEmitterAction::start(SceneTimelineInfo* info)
{
    const std::string result = info->executeEL(m_executeIf);
    m_isRunning = result == "true";
    
    enum ParticleEmitterType {
        NOT_FOLLOW_NOT_TIMEOUT = 0x0000,
        NOT_FOLLOW_TIMEOUT     = 0x0001,
        FOLLOW_NOT_TIMEOUT     = 0x0002,
        FOLLOW_TIMEOUT         = 0x0003,
        NOT_RUNNING            = 0xFFFF
    } type;
    
     if (m_isRunning)
        type = (ParticleEmitterType) ( (m_hasTimeout ? 0x0001 : 0x0000) + (m_hasFollowEntityRef ? 0x0002 : 0x0000) );
    else
        type = NOT_RUNNING;
        
    if (m_isRunning && m_hasFollowEntityRef)
        m_followEntity = Core::resourceManager().entity(m_followEntityRef);
    else
        m_followEntity = NULL;
        
    switch(type) {
    case NOT_FOLLOW_NOT_TIMEOUT:
        m_particleEmitterId = Core::particleSystemManager().newParticleEmitter(m_initialPos, m_particleEmitterRef);
        break;
    case NOT_FOLLOW_TIMEOUT:
        m_particleEmitterId = Core::particleSystemManager().newParticleEmitter(m_initialPos, m_particleEmitterRef, m_timeout);
        break;
    case FOLLOW_NOT_TIMEOUT:
        m_particleEmitterId = Core::particleSystemManager().newParticleEmitter(m_followEntity, m_followOffset, m_particleEmitterRef);
        break;
    case FOLLOW_TIMEOUT:
        m_particleEmitterId = Core::particleSystemManager().newParticleEmitter(m_followEntity, m_followOffset, m_particleEmitterRef, m_timeout);
        break;
    case NOT_RUNNING:
        m_particleEmitterId = -1;
        break;
    }
        
    if (m_setIdAtParamName != "") {
        std::stringstream ss;
        ss << m_particleEmitterId;
        info->setParam(m_setIdAtParamName, ss.str());
    }
}

bool AddNewParticleEmitterAction::isBlocking()
{
	return false;
}

bool AddNewParticleEmitterAction::isFinished()
{
	return !m_hasTimeout || !m_isRunning || Core::particleSystemManager().particleEmitterExists(m_particleEmitterId);
}

void AddNewParticleEmitterAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
