#pragma once

#include <string>

class HudFaceView;

class AddFaceViewParam
{
public:
    virtual ~AddFaceViewParam() { }
    virtual int id() const = 0;
    virtual const std::string& name() const = 0;
    virtual HudFaceView* generateFaceView() const = 0;
};
