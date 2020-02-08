#pragma once

#include <tinyxml.h>

#include <KYEngine/AddFaceViewParam.h>
#include <KYEngine/AddMapViewParam.h>
#include <KYEngine/AddProgressViewParam.h>
#include <KYEngine/AddJoystickButtonParam.h>
#include <KYEngine/AddPushButtonParam.h>
#include <KYEngine/AddTextLabelParam.h>
#include <KYEngine/HudMapViewItem.h>

#include <KYEngine/PlayingHud.h>
#include <KYEngine/PlayingHudFactoryListener.h>
#include <KYEngine/PlayingHudListener.h>

#include <KYEngine/Private/Huds/HudAnimations.h>
#include <KYEngine/Private/Huds/HudButton.h>
#include <KYEngine/Private/Huds/HudButtonListener.h>
#include <KYEngine/Private/Huds/HudFaceView.h>
#include <KYEngine/Private/Huds/HudJoystickButton.h>
#include <KYEngine/Private/Huds/HudMapView.h>
#include <KYEngine/Private/Huds/HudProgressView.h>
#include <KYEngine/Private/Huds/HudPushButton.h>
#include <KYEngine/Private/Huds/HudTextLabel.h>
#include <KYEngine/Private/Resources/Resource.h>

#include <KYEngine/Mesh.h>
#include <KYEngine/RenderLayer.h>

#include <list>
#include <map>
#include <string>

class HudManager;

class PlayingHudResource
    : public Resource
    , public PlayingHud
    , public PlayingHudFactoryListener
    , public HudButtonListener
{
public:
    PlayingHudResource();
    virtual ~PlayingHudResource();
    
public:
	static const std::string XML_NODE;
	static PlayingHudResource* readFromXml(TiXmlElement* node);

// Resource implementation
public:
	const std::string& name() const { return m_name; }
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }

// PlayingHud implementation
public:
    void appear(PlayingHudListener* listener);
    bool isAppeared() const;
    void disappear();
    bool isDisappeared() const;
    void abort();
    void setListener(PlayingHudListener* listener);
    const Vector4 direction(int id = 0);
    void setFaceValue(int id, double value);
    void setMapItems(int id, const std::list<HudMapViewItem>& items);
    void setProgressValue(int id, double value);
    void setTextLabel(int id, const std::string& value);
    void update(const double elapsedTime);

// PlayingHudFactoryListener implementation
public:
    void addFaceViewParam(AddFaceViewParam* faceViewParam) { m_faceViewParams.push_back(faceViewParam); }
    void addMapViewParam(AddMapViewParam* mapViewParam) { m_mapViewParams.push_back(mapViewParam); }
    void addProgressViewParam(AddProgressViewParam* progressViewParam) { m_progressViewParams.push_back(progressViewParam); }
	void addJoystickButtonParam(AddJoystickButtonParam* joystickButtonParam) { m_joystickButtonParams.push_back(joystickButtonParam); }
	void addPushButtonParam(AddPushButtonParam* pushButtonParam) { m_pushButtonParams.push_back(pushButtonParam); }
    void addTextLabelParam(AddTextLabelParam* textLabelParam) { m_textLabelParams.push_back(textLabelParam); }
    
private:
    void setName(const std::string& name) { m_name = name; }
    void setLayerName(const std::string& layerName) { m_layerName = layerName; }
    void setZOrder(double zOrder) { m_zOrder = zOrder; }
    
private:
	void addFaceView(int id, HudFaceView* view);
    void addProgressView(int id, HudProgressView* view);
    void addJoystickButton(int id, HudJoystickButton* button);
    void addMapView(int id, HudMapView* view);
    void addPushButton(int id, HudPushButton* button);
    void addTextLabel(int id, HudTextLabel* textLabel);
    
// HudButtonListener implementation
public:
    void hudButtonPressed(int id);
    void hudButtonReleased(int id);
    
private:
    std::string m_name;
    std::string m_layerName;
    double m_zOrder;
    std::list<AddFaceViewParam*> m_faceViewParams;
    std::list<AddMapViewParam*> m_mapViewParams;
    std::list<AddProgressViewParam*> m_progressViewParams;
    std::list<AddJoystickButtonParam*> m_joystickButtonParams;
    std::list<AddPushButtonParam*> m_pushButtonParams;
    std::list<AddTextLabelParam*> m_textLabelParams;
    
    RenderLayer* m_layer;
    PlayingHudListener* m_listener;
    std::map<int, HudFaceView*> m_faceViews;
    std::map<int, HudJoystickButton*> m_joystickButtons;
    std::map<int, HudMapView*> m_mapViews;
    std::map<int, HudProgressView*> m_progressViews;
    std::map<int, HudPushButton*> m_pushButtons;
    std::map<int, HudTextLabel*> m_textLabels;
};