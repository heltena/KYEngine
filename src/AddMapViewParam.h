#pragma once

#include <string>

class HudMapView;

class AddMapViewParam
{
public:
    virtual ~AddMapViewParam() { }
    virtual int id() const = 0;
    virtual const std::string& name() const = 0;
    virtual HudMapView* generateMapView() const = 0;
};
