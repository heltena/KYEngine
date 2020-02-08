#pragma once

class AddFaceViewParam;
class AddMapViewParam;
class AddProgressViewParam;
class AddPushButtonParam;
class AddTextLabelParam;

class PlayingHudFactoryListener
{
public:
    virtual void addFaceViewParam(AddFaceViewParam* faceViewParam) = 0;
    virtual void addMapViewParam(AddMapViewParam* mapViewParam) = 0;
    virtual void addProgressViewParam(AddProgressViewParam* progressViewParam) = 0;
	virtual void addJoystickButtonParam(AddJoystickButtonParam* joystickButtonParam) = 0;
	virtual void addPushButtonParam(AddPushButtonParam* pushButtonParam) = 0;
    virtual void addTextLabelParam(AddTextLabelParam* textLabelParam) = 0;
};