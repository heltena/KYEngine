#pragma once

#include <string>

class HudJoystickButton;

class AddJoystickButtonParam
{
public:
    virtual ~AddJoystickButtonParam() { }
    virtual int id() const = 0;
    virtual const std::string& name() const = 0;
    virtual HudJoystickButton* generateJoystickButton() const = 0;
};
