#include <KYEngine/Core.h>
#include <KYEngine/DialogInfo.h>
#include <KYEngine/SceneTimelineInfo.h>
#include <KYEngine/Private/AnimSceneActions/ShowDialogAction.h>
#include <KYEngine/Private/Resources/TextLayerEntityResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <stdexcept>

const std::string ShowDialogAction::XML_NODE = "show-dialog";

ShowDialogAction::ShowDialogAction()
{
}

ShowDialogAction::~ShowDialogAction()
{
}

ShowDialogAction* ShowDialogAction::readFromXml(TiXmlElement* node)
{
    const DialogInfo& info = Core::infoManager().dialogInfo();
	ShowDialogAction* action = new ShowDialogAction();
    
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string backgroundEntityRef = TiXmlHelper::readString(node, "background-entity-ref", false, info.backgroundEntityRef());
    double z = TiXmlHelper::readDouble(node, "z", false, info.z());
    double appearingCelerity = TiXmlHelper::readDouble(node, "appearing-celerity", false, info.appearingCelerity());
    double disappearingCelerity = TiXmlHelper::readDouble(node, "disappearing-celerity", false, info.disappearingCelerity());
    const std::string fontRef = TiXmlHelper::readString(node, "font-ref", false, info.fontRef());
    const double borderWidth = TiXmlHelper::readDouble(node, "border-width", false, info.borderWidth());
    const double borderHeight = TiXmlHelper::readDouble(node, "border-height", false, info.borderHeight());
    
	action->setName(name);
    action->setBackgroundEntityRef(backgroundEntityRef);
    action->setZ(z);
    action->setAppearingCelerity(appearingCelerity);
    action->setDisapparingCelerity(disappearingCelerity);
    action->setFontRef(fontRef);
    action->setBorderWidth(borderWidth);
    action->setBorderHeight(borderHeight);
    
    TiXmlElement* curr = node->FirstChildElement();
    while (curr) {
        const std::string& value = curr->Value();
        if (value == ShowDialogPhraseParam::XML_NODE) {
            ShowDialogPhraseParam* param = ShowDialogPhraseParam::readFromXml(curr);
            action->addTextParam(*param);
            delete param;
        } else 
            throw std::runtime_error("ShowDialogAction tag error: " + value);
        
        curr = curr->NextSiblingElement();
    }
    
    return action;
}

void ShowDialogAction::start(SceneTimelineInfo* info)
{
    double lineLength = Core::renderManager().width() - m_borderWidth * 2;
    double lineSpacing = 1;
    
    m_backgroundEntity = Core::resourceManager().entity(m_backgroundEntityRef);
    TextLayerEntityResource* entity = new TextLayerEntityResource();
    entity->setName("#textLayer");
    entity->setFontRef(m_fontRef);
    entity->setLineLength(lineLength);
    entity->setLineSpacing(lineSpacing);
    entity->setAlign(ALIGN_LEFT);
    entity->setDefaultText("");
    entity->setInitialPos(m_pos);
    entity->setUseBlending(true);
    entity->setColor(Vector4::WHITE);
    entity->setBorderColor(Vector4::BLACK);
    entity->load();
    info->layer()->addEntity(entity, true);
    m_entity = entity;

    setFirstText(info);
    
    info->layer()->addEntity(m_backgroundEntity);
    
    appear(info);
}

void ShowDialogAction::stop(SceneTimelineInfo* info)
{
    info->layer()->removeEntity(m_entity);
    info->layer()->removeEntity(m_backgroundEntity);
    m_entity = NULL;
    m_backgroundEntity = NULL;
}

bool ShowDialogAction::isBlocking()
{
	return true;
}

bool ShowDialogAction::isFinished()
{
	return m_state == FINISHED;
}

void ShowDialogAction::update(const double elapsedTime, SceneTimelineInfo* info)
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
    case CHANGE_HEIGHT:
        updateChangeHeight(elapsedTime, info);
        break;
    case DISAPPEARING:
        updateDisappearing(elapsedTime, info);
        break;
    case FINISHED:
        break;
    }
}

void ShowDialogAction::actionUnblocked(SceneTimelineInfo* info)
{
    if (m_currentTextParam == m_textParams.end() && m_currentMessageId == m_currentMessageCount)
        disappear(info);
    else
        changeToNextText(info);
}

void ShowDialogAction::setFirstText(SceneTimelineInfo* info)
{
    m_currentTextParam = m_textParams.begin();
    m_currentTime = m_currentTextParam->time();
    m_useTime = m_currentTextParam->useTime();
    m_currentColor = m_currentTextParam->color();
    m_currentKey = Core::i18nManager().keyFromString(m_currentTextParam->text());
    m_currentTextParam++;
    m_currentMessageId = 0;
    m_currentMessageCount = Core::i18nManager().messageCount(m_currentKey);
    m_currentText = Core::i18nManager().message(m_currentKey, m_currentMessageId);
    m_currentMessageId++;
    TextLayerExtension* extension = m_entity->textLayerInterface();
    if (extension)
        extension->setText(m_currentText);
    m_entity->setColor(m_currentColor);

    if (!m_useTime)
        m_mustRegister = true;
}

void ShowDialogAction::appear(SceneTimelineInfo* info)
{
    if (m_appearingCelerity == 0)
        show(info);
    else {
        m_toPosY = m_entity->screenBounds().height() + m_borderHeight * 2;
        m_fromPosY = 0;
        
        setPos(Vector4(0, m_fromPosY, m_z));
        m_state = APPEARING;
    }
}

void ShowDialogAction::show(SceneTimelineInfo* info)
{
    if (m_useTime)
        m_timeout = m_currentTime;
    setPos(Vector4(0, m_entity->screenBounds().height() + m_borderHeight * 2, m_z));
    m_state = SHOWING;
}

void ShowDialogAction::changeToNextText(SceneTimelineInfo* info)
{
    if (m_currentMessageId == m_currentMessageCount) {
        m_currentTime = m_currentTextParam->time();
        m_useTime = m_currentTextParam->useTime();
        m_currentColor = m_currentTextParam->color();
        m_entity->setColor(m_currentColor);
        m_currentKey = Core::i18nManager().keyFromString(m_currentTextParam->text());
        m_currentTextParam++;
        m_currentMessageId = 0;
        m_currentMessageCount = Core::i18nManager().messageCount(m_currentKey);
    }
    m_currentText = Core::i18nManager().message(m_currentKey, m_currentMessageId);
        TextLayerExtension* extension = m_entity->textLayerInterface();
    if (extension)
        extension->setText(m_currentText);
    m_currentMessageId++;

    m_fromPosY = m_toPosY;
    m_toPosY = m_entity->screenBounds().height() + m_borderHeight * 2;
    m_state = CHANGE_HEIGHT;
    if (!m_useTime)
        m_mustRegister = true;
}

void ShowDialogAction::disappear(SceneTimelineInfo* info)
{
    if (m_disappearingCelerity == 0 || m_entity == NULL)
        hide(info);
    else {
        m_fromPosY = m_entity->screenBounds().height() + m_borderHeight * 2;
        m_toPosY = 0;
        setPos(Vector4(0, m_fromPosY, m_z));
        m_state = DISAPPEARING;
    }
}

void ShowDialogAction::hide(SceneTimelineInfo* info)
{
    m_state = FINISHED;
    m_fromPosY = m_toPosY;
    setPos(Vector4(0, m_fromPosY, m_z));
}

void ShowDialogAction::updateAppearing(const double elapsedTime, SceneTimelineInfo* info)
{
    double epsilon = m_toPosY - m_fromPosY;
    if (fabs(epsilon) < 1) {
        show(info);
        m_fromPosY = m_toPosY;
    } else {
        m_fromPosY += epsilon * m_appearingCelerity * elapsedTime;
        if ( (epsilon > 0 && m_fromPosY > m_toPosY) || (epsilon < 0 && m_fromPosY < m_toPosY) )
            m_fromPosY = m_toPosY;
    }
    setPos(Vector4(0, m_fromPosY, m_z));
}

void ShowDialogAction::updateShowing(const double elapsedTime, SceneTimelineInfo* info)
{
    m_timeout -= elapsedTime;
    if (m_useTime && m_timeout < 0) {
        if (m_currentTextParam == m_textParams.end() && m_currentMessageId == m_currentMessageCount)
            disappear(info);
        else
            changeToNextText(info);
    }
}

void ShowDialogAction::updateChangeHeight(const double elapsedTime, SceneTimelineInfo* info)
{
    double epsilon = m_toPosY - m_fromPosY;
    if (fabs(epsilon) < 1) {
        m_state = SHOWING;
        m_timeout = m_currentTime;
        m_fromPosY = m_toPosY;
    } else {
        m_fromPosY += epsilon * m_appearingCelerity * elapsedTime;
        if ( (epsilon > 0 && m_fromPosY > m_toPosY) || (epsilon < 0 && m_fromPosY < m_toPosY) )
            m_fromPosY = m_toPosY;
    }
    setPos(Vector4(0, m_fromPosY, m_z));
}

void ShowDialogAction::updateDisappearing(const double elapsedTime, SceneTimelineInfo* info)
{
    double epsilon = m_toPosY - m_fromPosY;
    if (fabs(epsilon) < 1) {
        m_state = FINISHED;
        m_fromPosY = m_toPosY;
    } else {
        m_fromPosY += epsilon * m_appearingCelerity * elapsedTime;
        if ( (epsilon > 0 && m_fromPosY > m_toPosY) || (epsilon < 0 && m_fromPosY < m_toPosY) )
            m_fromPosY = m_toPosY;
    }
    setPos(Vector4(0, m_fromPosY, m_z));
}

void ShowDialogAction::setPos(const Vector4& pos)
{
    Vector4 bPos = pos;
    bPos[0] = 480;
    m_backgroundEntity->setPos(bPos);
    Vector4 ePos = pos;
    ePos[0] += m_borderWidth;
    ePos[1] -= m_borderHeight;
    ePos[2] += 0.1;
    m_entity->setPos(ePos);
    m_pos = pos;
}