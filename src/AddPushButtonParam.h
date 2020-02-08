#pragma once

#include <string>

class HudPushButton;

class AddPushButtonParam
{
public:
    virtual ~AddPushButtonParam() { }
    virtual int id() const = 0;
    virtual const std::string& name() const = 0;
    virtual HudPushButton* generatePushButton() const = 0;
};
