#pragma once

#include <KYEngine/HudMapViewItem.h>
#include <KYEngine/PlayingHudListener.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>
#include <map>
#include <string>

class PlayingHud
{
public:
    virtual ~PlayingHud() { }
    virtual const std::string& name() const = 0;
    virtual void appear(PlayingHudListener* listener) = 0;
    virtual bool isAppeared() const = 0;
    virtual void disappear() = 0;
    virtual bool isDisappeared() const = 0;
    virtual void abort() = 0;
    virtual void setListener(PlayingHudListener* listener) = 0;
    virtual const Vector4 direction(int id = 0) = 0;
    virtual void setFaceValue(int id, double value) = 0;
    virtual void setMapItems(int id, const std::list<HudMapViewItem>& items) = 0;
    virtual void setProgressValue(int id, double value) = 0;
    virtual void setTextLabel(int id, const std::string& value) = 0;
    virtual void update(const double elapsedTime) = 0;
};