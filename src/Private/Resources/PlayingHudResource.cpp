#include <KYEngine/AddFaceViewParam.h>
#include <KYEngine/AddMapViewParam.h>
#include <KYEngine/AddProgressViewParam.h>
#include <KYEngine/AddJoystickButtonParam.h>
#include <KYEngine/AddPushButtonParam.h>
#include <KYEngine/Core.h>
#include <KYEngine/Private/Resources/PlayingHudResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

const std::string PlayingHudResource::XML_NODE = "playing-hud";

PlayingHudResource::PlayingHudResource()
    : m_listener(NULL)
    , m_layer(NULL)
{
}

PlayingHudResource::~PlayingHudResource()
{
}

PlayingHudResource* PlayingHudResource::readFromXml(TiXmlElement* node)
{
    PlayingHudResource* result = new PlayingHudResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string layerName = TiXmlHelper::readString(node, "layer-name", true);
    double zOrder = TiXmlHelper::readDouble(node, "z-order", true);
    
	result->setName(name);
    result->setLayerName(layerName);
    result->setZOrder(zOrder);
    
    TiXmlElement* curr = node->FirstChildElement();
    while (curr) {
        std::string prefix = Core::resourceManager().prefixOfNode(curr);
        Core::resourceManager().factory(prefix)->readFromXml(prefix, curr, result);
        curr = curr->NextSiblingElement();
    }

    return result;
}

void PlayingHudResource::preload()
{
}

void PlayingHudResource::unloadFromPreloaded()
{
}

void PlayingHudResource::load()
{
    for(std::list<AddFaceViewParam*>::const_iterator it = m_faceViewParams.begin(); it != m_faceViewParams.end(); it++) {
        AddFaceViewParam* faceViewParam = *it;
        HudFaceView* view = faceViewParam->generateFaceView();
        addFaceView(faceViewParam->id(), view);
    }
    
    for(std::list<AddMapViewParam*>::const_iterator it = m_mapViewParams.begin(); it != m_mapViewParams.end(); it++) {
        AddMapViewParam* mapViewParam = *it;
        HudMapView* view = mapViewParam->generateMapView();
        addMapView(mapViewParam->id(), view);
    }
    
    for(std::list<AddProgressViewParam*>::const_iterator it = m_progressViewParams.begin(); it != m_progressViewParams.end(); it++) {
        AddProgressViewParam* progressViewParam = *it;
        HudProgressView* view = progressViewParam->generateProgressView();
        addProgressView(progressViewParam->id(), view);
    }
    
    for(std::list<AddJoystickButtonParam*>::const_iterator it = m_joystickButtonParams.begin(); it != m_joystickButtonParams.end(); it++) {
        AddJoystickButtonParam* joystickButtonParam = *it;
        HudJoystickButton* button = joystickButtonParam->generateJoystickButton();
        addJoystickButton(joystickButtonParam->id(), button);
    }
    
    for(std::list<AddPushButtonParam*>::const_iterator it = m_pushButtonParams.begin(); it != m_pushButtonParams.end(); it++) {
        AddPushButtonParam* pushButtonParam = *it;
        HudPushButton* button = pushButtonParam->generatePushButton();
        addPushButton(pushButtonParam->id(), button);
    }
    
    for(std::list<AddTextLabelParam*>::const_iterator it = m_textLabelParams.begin(); it != m_textLabelParams.end(); it++) {
        AddTextLabelParam* textLabelParam = *it;
        HudTextLabel* textLabel = textLabelParam->generateTextLabel();
        addTextLabel(textLabelParam->id(), textLabel);
    }
}

void PlayingHudResource::unload()
{
    m_listener = NULL;
 
    
    if (m_layer) {
        Core::renderManager().removeLayer(m_layerName);
        m_layer = NULL;
    }
    
    for(std::map<int, HudFaceView*>::const_iterator it = m_faceViews.begin(); it != m_faceViews.end(); it++)
        delete it->second;
    m_faceViews.clear();
    
    for(std::map<int, HudMapView*>::const_iterator it = m_mapViews.begin(); it != m_mapViews.end(); it++)
        delete it->second;
    m_joystickButtons.clear();
    
    for(std::map<int, HudProgressView*>::const_iterator it = m_progressViews.begin(); it != m_progressViews.end(); it++)
        delete it->second;
    m_mapViews.clear();
    
    for(std::map<int, HudJoystickButton*>::const_iterator it = m_joystickButtons.begin(); it != m_joystickButtons.end(); it++)
        delete it->second;
    m_progressViews.clear();
    
    for(std::map<int, HudPushButton*>::const_iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); it++)
        delete it->second;
    m_pushButtons.clear();
    
    for(std::map<int, HudTextLabel*>::const_iterator it = m_textLabels.begin(); it != m_textLabels.end(); it++)
        delete it->second;
    m_textLabels.clear();
}

void PlayingHudResource::appear(PlayingHudListener* listener)
{
    if (m_layer == NULL)
        m_layer = Core::renderManager().createLayer(m_layerName, m_zOrder);    
    
    m_listener = listener;
    for (std::map<int, HudFaceView*>::iterator it = m_faceViews.begin(); it != m_faceViews.end(); it++) {
        it->second->appear();
        m_layer->addEntity(it->second);
    }
    for (std::map<int, HudMapView*>::iterator it = m_mapViews.begin(); it != m_mapViews.end(); it++) {
        it->second->appear();
        m_layer->addEntity(it->second);
    }
    for (std::map<int, HudJoystickButton*>::iterator it = m_joystickButtons.begin(); it != m_joystickButtons.end(); it++) {
        it->second->appear(NULL);
        m_layer->addEntity(it->second);
    }
    for (std::map<int, HudProgressView*>::iterator it = m_progressViews.begin(); it != m_progressViews.end(); it++) {
        it->second->appear();
        m_layer->addEntity(it->second);
    }
    for (std::map<int, HudPushButton*>::iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); it++) {
        it->second->appear(this);
        m_layer->addEntity(it->second);
    }
    for(std::map<int, HudTextLabel*>::iterator it = m_textLabels.begin(); it != m_textLabels.end(); it++) {
        it->second->appear();
        m_layer->addEntity(it->second);
    }
}

bool PlayingHudResource::isAppeared() const
{
    for (std::map<int, HudFaceView*>::const_iterator it = m_faceViews.begin(); it != m_faceViews.end(); it++) {
        if (! it->second->isAppeared())
            return false;
    }
    for (std::map<int, HudMapView*>::const_iterator it = m_mapViews.begin(); it != m_mapViews.end(); it++) {
        if (! it->second->isAppeared())
            return false;
    }
    for (std::map<int, HudJoystickButton*>::const_iterator it = m_joystickButtons.begin(); it != m_joystickButtons.end(); it++) {
        if (! it->second->isAppeared())
            return false;
    }
    for (std::map<int, HudProgressView*>::const_iterator it = m_progressViews.begin(); it != m_progressViews.end(); it++) {
        if (! it->second->isAppeared())
            return false;
    }
    for (std::map<int, HudPushButton*>::const_iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); it++) {
        if (! it->second->isAppeared())
            return false;
    }
    for(std::map<int, HudTextLabel*>::const_iterator it = m_textLabels.begin(); it != m_textLabels.end(); it++) {
        if (! it->second->isAppeared())
            return false;
    }

    return true;
}

void PlayingHudResource::disappear()
{
    m_listener = NULL;
    for (std::map<int, HudFaceView*>::iterator it = m_faceViews.begin(); it != m_faceViews.end(); it++) {
        it->second->disappear();
    }
    for (std::map<int, HudMapView*>::iterator it = m_mapViews.begin(); it != m_mapViews.end(); it++) {
        it->second->disappear();
    }
    for (std::map<int, HudJoystickButton*>::iterator it = m_joystickButtons.begin(); it != m_joystickButtons.end(); it++) {
        it->second->disappear();
    }
    for (std::map<int, HudProgressView*>::iterator it = m_progressViews.begin(); it != m_progressViews.end(); it++) {
        it->second->disappear();
    }
    for (std::map<int, HudPushButton*>::iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); it++) {
        it->second->disappear();
    }
    for(std::map<int, HudTextLabel*>::iterator it = m_textLabels.begin(); it != m_textLabels.end(); it++) {
        it->second->disappear();
    }

    m_listener = NULL;
}

bool PlayingHudResource::isDisappeared() const
{
    for (std::map<int, HudFaceView*>::const_iterator it = m_faceViews.begin(); it != m_faceViews.end(); it++) {
        if (! it->second->isDisappeared())
            return false;
    }
    for (std::map<int, HudMapView*>::const_iterator it = m_mapViews.begin(); it != m_mapViews.end(); it++) {
        if (! it->second->isDisappeared())
            return false;
    }
    for (std::map<int, HudJoystickButton*>::const_iterator it = m_joystickButtons.begin(); it != m_joystickButtons.end(); it++) {
        if (! it->second->isDisappeared())
            return false;
    }
    for (std::map<int, HudProgressView*>::const_iterator it = m_progressViews.begin(); it != m_progressViews.end(); it++) {
        if (! it->second->isDisappeared())
            return false;
    }
    for (std::map<int, HudPushButton*>::const_iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); it++) {
        if (! it->second->isDisappeared())
            return false;
    }
    for(std::map<int, HudTextLabel*>::const_iterator it = m_textLabels.begin(); it != m_textLabels.end(); it++) {
        if (! it->second->isDisappeared())
            return false;
    }

    return true;
}

void PlayingHudResource::abort()
{
    if (m_layer != NULL) {
        Core::renderManager().removeLayer(m_layerName);
        m_layer = NULL;
    }
}

void PlayingHudResource::setListener(PlayingHudListener* listener)
{
    m_listener = listener;
}

const Vector4 PlayingHudResource::direction(int id)
{
    std::map<int, HudJoystickButton*>::iterator it = m_joystickButtons.find(id);
    if (it == m_joystickButtons.end())
        return Vector4();
    return it->second->direction();
}

void PlayingHudResource::setFaceValue(int id, double value)
{
    std::map<int, HudFaceView*>::iterator it = m_faceViews.find(id);
    if (it == m_faceViews.end())
        throw std::runtime_error("PlayingHud: faceView not found " + id);
    it->second->setCurrentValue(value);
}

void PlayingHudResource::setMapItems(int id, const std::list<HudMapViewItem>& items)
{
    std::map<int, HudMapView*>::iterator it = m_mapViews.find(id);
    if (it == m_mapViews.end())
        throw std::runtime_error("PlayingHud: mapView not found " + id);
    it->second->setItems(items);
}

void PlayingHudResource::setProgressValue(int id, double value)
{
    std::map<int, HudProgressView*>::iterator it = m_progressViews.find(id);
    if (it == m_progressViews.end())
        throw std::runtime_error("PlayingHud: progressView not found " + id);
    it->second->setCurrentValue(value);
}

void PlayingHudResource::setTextLabel(int id, const std::string& value)
{
    std::map<int, HudTextLabel*>::iterator it = m_textLabels.find(id);
    if (it == m_textLabels.end())
        throw std::runtime_error("PlayingHud: textLabel not found " + id);
    it->second->setText(value);
}

void PlayingHudResource::update(const double elapsedTime)
{
    if (m_layer == NULL)
        return;
    
    if (isDisappeared()) {
        if (m_layer != NULL) {
            Core::renderManager().removeLayer(m_layerName);
            m_layer = NULL;
        }
    } else {
        for (std::map<int, HudFaceView*>::iterator it = m_faceViews.begin(); it != m_faceViews.end(); it++)
            it->second->update(elapsedTime);
        for (std::map<int, HudMapView*>::iterator it = m_mapViews.begin(); it != m_mapViews.end(); it++)
            it->second->update(elapsedTime);
        for (std::map<int, HudJoystickButton*>::iterator it = m_joystickButtons.begin(); it != m_joystickButtons.end(); it++)
            it->second->update(elapsedTime);
        for (std::map<int, HudProgressView*>::iterator it = m_progressViews.begin(); it != m_progressViews.end(); it++)
            it->second->update(elapsedTime);
        for (std::map<int, HudPushButton*>::iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); it++)
            it->second->update(elapsedTime);
        for (std::map<int, HudTextLabel*>::iterator it = m_textLabels.begin(); it != m_textLabels.end(); it++)
            it->second->update(elapsedTime);
    }
}

void PlayingHudResource::addFaceView(int id, HudFaceView* view)
{
    m_faceViews[id] = view;
}

void PlayingHudResource::addJoystickButton(int id, HudJoystickButton* button)
{
    m_joystickButtons[id] = button;
}

void PlayingHudResource::addMapView(int id, HudMapView* view)
{
    m_mapViews[id] = view;
}

void PlayingHudResource::addProgressView(int id, HudProgressView* view)
{
    m_progressViews[id] = view;
}

void PlayingHudResource::addPushButton(int id, HudPushButton* button)
{
    m_pushButtons[id] = button;
}

void PlayingHudResource::addTextLabel(int id, HudTextLabel* textLabel)
{
    m_textLabels[id] = textLabel;
}

void PlayingHudResource::hudButtonPressed(int id)
{
    if (m_listener)
        m_listener->hudButtonPressed(direction(), id);
}

void PlayingHudResource::hudButtonReleased(int id)
{
    if (m_listener)
        m_listener->hudButtonReleased(direction(), id);
}



