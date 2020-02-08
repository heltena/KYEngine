#include <KYEngine/Atrezzo.h>
#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/UseAtrezzoAction.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string UseAtrezzoAction::XML_NODE = "use-atrezzo";

UseAtrezzoAction::UseAtrezzoAction()
{
}

UseAtrezzoAction::~UseAtrezzoAction()
{
}

UseAtrezzoAction* UseAtrezzoAction::readFromXml(TiXmlElement* node)
{
	UseAtrezzoAction* action = new UseAtrezzoAction();
    
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string atrezzoRef = TiXmlHelper::readString(node, "atrezzo-ref", true);
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", READ_X | READ_Y | READ_Z);
    const Vector4 cameraPos = TiXmlHelper::readVector(node, "cx", "cy", "cz", "", READ_X | READ_Y | READ_Z);
    
	action->setName(name);
    action->setAtrezzoRef(atrezzoRef);
    action->setInitialPos(initialPos);
    action->setCameraPos(cameraPos);
    
    return action;
}

void UseAtrezzoAction::start(SceneTimelineInfo* info)
{
    Atrezzo* atrezzo = Core::resourceManager().atrezzo(m_atrezzoRef);
    Entity* entity = atrezzo->asEntity();
    info->layer()->addEntity(entity);
    entity->setPos(m_initialPos);
    atrezzo->setCameraPos(m_cameraPos);
}

bool UseAtrezzoAction::isBlocking()
{
	return false;
}

bool UseAtrezzoAction::isFinished()
{
	return true;
}

void UseAtrezzoAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
