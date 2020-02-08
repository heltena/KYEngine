#include <KYEngine/Private/AnimSceneActions/AddTouchEventAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Sound.h>
#include <KYEngine/Utility/TiXmlHelper.h>

const double AddTouchEventAction::TOUCH_TIMEOUT = 0.75;
const std::string AddTouchEventAction::XML_NODE = "add-touch-event";

AddTouchEventAction::AddTouchEventAction()
{
}

AddTouchEventAction::~AddTouchEventAction()
{
}

AddTouchEventAction* AddTouchEventAction::readFromXml(TiXmlElement* node)
{
	AddTouchEventAction* action = new AddTouchEventAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
	const std::string entityRef = TiXmlHelper::readString(node, "entity-ref", true);
    const std::string animReleased = TiXmlHelper::readString(node, "anim-released", false, "released");
    const std::string animOver = TiXmlHelper::readString(node, "anim-over", false, "over");
    const std::string soundRef = TiXmlHelper::readString(node, "sound-ref", false, "click");
	const std::string script = TiXmlHelper::readString(node, "script", true);
    const Vector4 boundsAddSize = TiXmlHelper::readVector(node, "bsx", "bsy", "", "", NO_READ, 0, 0, 0, 0);
    
    bool useTelemetry;
    std::string telemetryCategory;
    std::string telemetryAction;
    std::string telemetryLabel;
    int telemetryValue = 0;
    
    useTelemetry = TiXmlHelper::containsAttribute(node, "telemetry-category");
    if (useTelemetry) {
        telemetryCategory = TiXmlHelper::readString(node, "telemetry-category", true);
        telemetryAction = TiXmlHelper::readString(node, "telemetry-action", true);
        telemetryLabel = TiXmlHelper::readString(node, "telemetry-label", false, "");
        telemetryValue = TiXmlHelper::readInt(node, "telemetry-value", false, 0);
    }
    
	action->setName(name);
	action->setEntityRef(entityRef);
    action->setAnimReleased(animReleased);
    action->setAnimOver(animOver);
    action->setSoundRef(soundRef);
	action->setScript(script);
    action->setBoundsAddSize(boundsAddSize);
    
    action->setUseTelemetry(useTelemetry);
    action->setTelemetryCategory(telemetryCategory);
    action->setTelemetryAction(telemetryAction);
    action->setTelemetryLabel(telemetryLabel);
    action->setTelemetryValue(telemetryValue);

	return action;
}

void AddTouchEventAction::start(SceneTimelineInfo* info)
{
	info->addTouchEvent(this);
    if (m_entityRef == "#dark-background")
        m_entity = info->darkEntity();
    else
        m_entity = Core::resourceManager().entity(m_entityRef);
    m_sound = Core::resourceManager().soundBuffer(m_soundRef);
    m_curAnimReleased = info->executeEL(m_animReleased);
    m_curAnimOver = info->executeEL(m_animOver);
}

bool AddTouchEventAction::isBlocking()
{
	return false;
}

bool AddTouchEventAction::isFinished()
{
	return true;
}

void AddTouchEventAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    m_touchTimeout -= elapsedTime;
    if (m_touchTimeout < 0)
        m_entity->setAnim(m_curAnimReleased);
}

void AddTouchEventAction::touchOver(int touchId, SceneTimelineInfo* info)
{
    m_touchId = touchId;
    m_entity->setAnim(m_curAnimOver);
    m_touchTimeout = TOUCH_TIMEOUT;
}

void AddTouchEventAction::touchMovedOut(SceneTimelineInfo* info)
{
    m_entity->setAnim(m_curAnimReleased);
    m_touchTimeout = TOUCH_TIMEOUT;
}

void AddTouchEventAction::touchMovedIn(SceneTimelineInfo* info)
{
    m_entity->setAnim(m_curAnimOver);
    m_touchTimeout = TOUCH_TIMEOUT;
}

void AddTouchEventAction::touchReleased(SceneTimelineInfo* info)
{
    m_entity->setAnim(m_curAnimReleased);
    Core::soundManager().playSimpleSound(m_sound);
    m_touchId = -1;
    m_touchTimeout = TOUCH_TIMEOUT;
}

void AddTouchEventAction::touchCancelled(SceneTimelineInfo* info)
{
    m_entity->setAnim(m_curAnimReleased);
    m_touchId = -1;
    m_touchTimeout = TOUCH_TIMEOUT;
}

const Box AddTouchEventAction::screenBounds() const
{
    Box b = m_entity->screenBounds();
    b.addSize(m_boundsAddSize[0], m_boundsAddSize[1]);
    return b;
}

void AddTouchEventAction::executeScript(SceneTimelineInfo *info)
{
    if (m_useTelemetry)
        Core::telemetryManager().trackEvent(m_telemetryCategory, m_telemetryAction, m_telemetryLabel, m_telemetryValue);
    info->executeEL(m_script);
}
