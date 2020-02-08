#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/PopupInfo.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/ShowPopupAction.h>
#include <KYEngine/Private/Resources/TextLayerEntityResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <stdexcept>

const std::string ShowPopupAction::XML_NODE = "show-popup";

ShowPopupAction::ShowPopupAction()
{
}

ShowPopupAction::~ShowPopupAction()
{
}

ShowPopupAction* ShowPopupAction::readFromXml(TiXmlElement* node)
{
    const PopupInfo& info = Core::infoManager().popupInfo();
	ShowPopupAction* action = new ShowPopupAction();
    
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string text = TiXmlHelper::readString(node, "text", true);
    const std::string backgroundEntityRef = TiXmlHelper::readString(node, "background-entity-ref", false, info.backgroundEntityRef());
    
    Vector4 pos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", NO_READ, info.pos());
    
    double appearDuration = TiXmlHelper::readDouble(node, "appear-duration", false, info.appearDuration());
    double appearAccelMagnitude = TiXmlHelper::readDouble(node, "appear-accel-magnitude", false, info.appearAccelMagnitude());
    EffectType appearEffect = TiXmlHelper::readEffect(node, "appear-effect", false, info.appearEffect());
    
    double disappearDuration = TiXmlHelper::readDouble(node, "disappear-duration", false, info.disappearDuration());
    double disappearAccelMagnitude = TiXmlHelper::readDouble(node, "disappear-accel-magnitude", false, info.disappearAccelMagnitude());
    EffectType disappearEffect = TiXmlHelper::readEffect(node, "disappear-effect", false, info.disappearEffect());
    
    const std::string fontRef = TiXmlHelper::readString(node, "font-ref", false, info.fontRef());
    const double borderWidth = TiXmlHelper::readDouble(node, "border-width", false, info.borderWidth());
    const double borderHeight = TiXmlHelper::readDouble(node, "border-height", false, info.borderHeight());
    const Vector4 color = TiXmlHelper::readVector(node, "r", "g", "b", "a", NO_READ, 1, 1, 1, 1);
    const AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_CENTER);
    const AlignType verticalAlign = TiXmlHelper::readAlignType(node, "vertical-align", false, ALIGN_CENTER);
    double lineLength = TiXmlHelper::readDouble(node, "line-length", false, 0);
    bool useTime = TiXmlHelper::containsAttribute(node, "time");
    double time = TiXmlHelper::readDouble(node, "time", false, 0);
    bool waitForTouch = TiXmlHelper::readBool(node, "wait-for-touch", false, !useTime);
    bool useBackground = TiXmlHelper::readBool(node, "use-background", false, info.useBackground());
    
	action->setName(name);
    action->setText(text);
    action->setBackgroundEntityRef(backgroundEntityRef);
    action->setPos(pos);
    action->setAppearDuration(appearDuration);
    action->setAppearAccelMagnitude(appearAccelMagnitude);
    action->setAppearEffect(appearEffect);
    action->setDisappearDuration(disappearDuration);
    action->setDisappearAccelMagnitude(disappearAccelMagnitude);
    action->setDisappearEffect(disappearEffect);
    action->setFontRef(fontRef);
    action->setBorderWidth(borderWidth);
    action->setBorderHeight(borderHeight);
    action->setColor(color);
    action->setAlign(align);
    action->setVerticalAlign(verticalAlign);
    action->setLineLength(lineLength);
    action->setUseTime(useTime);
    action->setTime(time);
    action->setWaitForTouch(waitForTouch);
    action->setUseBackground(useBackground);
    
    return action;
}

void ShowPopupAction::start(SceneTimelineInfo* info)
{
    if (m_lineLength == 0)
        m_lineLength = Core::renderManager().width() - m_borderWidth * 2;
    double lineSpacing = 1;
    
    TextLayerEntityResource* entity = new TextLayerEntityResource();
    entity->setFontRef(m_fontRef);
    entity->setLineLength(m_lineLength);
    entity->setLineSpacing(lineSpacing);
    entity->setAlign(m_align);
    entity->setDefaultText(info->executeEL(m_text));
    entity->setInitialPos(m_pos);
    entity->setUseBlending(true);
    entity->setColor(m_color);
    entity->setBorderColor(Vector4::BLACK);
    entity->load();
    m_entity = entity;
    m_box = entity->screenBounds();
    m_box.addSize(m_borderWidth * 2, m_borderHeight * 2);
    info->layer()->addEntity(entity, true);

    if (m_useBackground) {
        m_backgroundEntity = Core::resourceManager().entity(m_backgroundEntityRef);
        m_backgroundScale = Vector4(m_box.width(), m_box.height(), 1);
        m_backgroundEntity->setScale(m_backgroundScale);
        m_backgroundAlpha = m_backgroundEntity->color()[3];
        info->layer()->addEntity(m_backgroundEntity);
    }
    
    m_mustRegister = ! m_useTime && m_waitForTouch;

    double yOffset;
    switch(m_verticalAlign) {
    case ALIGN_TOP:
        yOffset = - m_box.height() / 2;
        break;
    case ALIGN_CENTER:
        yOffset = 0;
        break;
    case ALIGN_BOTTOM:
        yOffset = m_box.height() / 2;
        break;
    default:
        yOffset = 0;
    }
    
    m_showPos = m_pos;
    m_showPos[1] += yOffset;

    m_textOffset = Vector4(-m_lineLength / 2, m_box.height() / 2 - m_borderHeight, 0.1);
    
    switch(m_align) {
    case ALIGN_LEFT:
        m_textOffset[0] += m_borderWidth;
        break;
    case ALIGN_RIGHT:
        m_textOffset[0] -= m_borderWidth;
        break;
    default:
        break;
    }
    
    m_firstAppearPos = m_showPos;
    switch(m_appearEffect) {
    case EFFECT_NOTHING:
        m_appearDuration = 0;
        break;
    case EFFECT_LEFT:
        m_firstAppearPos[0] = - m_box.width();
        break;
    case EFFECT_RIGHT:
        m_firstAppearPos[0] = Core::renderManager().width() + m_box.width();
        break;
    case EFFECT_TOP:
        m_firstAppearPos[1] = - m_box.height();
        break;
    case EFFECT_BOTTOM:
        m_firstAppearPos[1] = Core::renderManager().height() + m_box.height();
        break;
    }
    
    m_disappearedPos = m_showPos;
    switch(m_disappearEffect) {
    case EFFECT_NOTHING:
        m_disappearDuration = 0;
        break;
    case EFFECT_LEFT:
        m_disappearedPos[0] = - m_box.width();
        break;
    case EFFECT_RIGHT:
        m_disappearedPos[0] = Core::renderManager().width() + m_box.width();
        break;
    case EFFECT_TOP:
        m_disappearedPos[1] = - m_box.height();
        break;
    case EFFECT_BOTTOM:
        m_disappearedPos[1] = Core::renderManager().height() + m_box.height();
        break;
    }
    
    appear(info);
}

void ShowPopupAction::stop(SceneTimelineInfo* info)
{
    info->layer()->removeEntity(m_entity);
    m_entity = NULL;
    if (m_useBackground) {
        info->layer()->removeEntity(m_backgroundEntity);
        m_backgroundEntity = NULL;
    }
}

bool ShowPopupAction::isBlocking()
{
	return m_useTime || m_waitForTouch;
}

bool ShowPopupAction::isFinished()
{
	return m_state == FINISHED;
}

void ShowPopupAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    if (m_mustRegister) {
        info->waitForGlobalTouch(this);
        m_mustRegister = false;
    }
    switch(m_state) {
    case APPEARING:
        updateAppearing(elapsedTime, info);
        break;
    case SHOWING:
        updateShowing(elapsedTime, info);
        break;
    case DISAPPEARING:
        updateDisappearing(elapsedTime, info);
        break;
    case FINISHED:
        break;
    }
}

void ShowPopupAction::actionUnblocked(SceneTimelineInfo* info)
{
    disappear(info);
}

void ShowPopupAction::appear(SceneTimelineInfo* info)
{
    if (m_appearDuration == 0)
        show(info);
    else {
        m_timeout = m_appearDuration;
        m_state = APPEARING;
        if (m_useBackground)
            m_backgroundEntity->setPos(m_firstAppearPos);
        m_entity->setPos(m_firstAppearPos + m_textOffset);
    }
}

void ShowPopupAction::show(SceneTimelineInfo* info)
{
    if (m_useTime)
        m_timeout = m_time;
    m_state = SHOWING;
    if (m_useBackground)
        m_backgroundEntity->setPos(m_showPos);
    m_entity->setPos(m_showPos + m_textOffset);
}

void ShowPopupAction::disappear(SceneTimelineInfo* info)
{
    if (m_disappearDuration == 0)
        hide(info);
    else {
        m_timeout = m_disappearDuration;
        m_state = DISAPPEARING;
    }
}

void ShowPopupAction::hide(SceneTimelineInfo* info)
{
    m_state = FINISHED;
    if (m_useBackground)
        m_backgroundEntity->setPos(m_disappearedPos);
    m_entity->setPos(m_disappearedPos + m_textOffset);
}

void ShowPopupAction::updateAppearing(const double elapsedTime, SceneTimelineInfo* info)
{
    m_timeout -= elapsedTime;
    if (m_timeout < 0)
        show(info);
    else {
        Vector4 pos = Vector4::interpolate(m_firstAppearPos, m_showPos, (m_appearDuration - m_timeout) / m_appearDuration, m_appearAccelMagnitude);
        if (m_useBackground)
            m_backgroundEntity->setPos(pos);
        m_entity->setPos(pos + m_textOffset);
    }
}

void ShowPopupAction::updateShowing(const double elapsedTime, SceneTimelineInfo* info)
{
    m_timeout -= elapsedTime;
    if (m_useTime && m_timeout < 0)
        disappear(info);
}

void ShowPopupAction::updateDisappearing(const double elapsedTime, SceneTimelineInfo* info)
{
    m_timeout -= elapsedTime;
    if (m_timeout < 0)
        hide(info);
    else {
        Vector4 pos = Vector4::interpolate(m_showPos, m_disappearedPos, (m_disappearDuration - m_timeout) / m_disappearDuration, m_disappearAccelMagnitude);
        if (m_useBackground)
            m_backgroundEntity->setPos(pos);
        m_entity->setPos(pos + m_textOffset);
    }
}
