#pragma once

#include <string>

class HudTextLabel;

class AddTextLabelParam
{
public:
    virtual ~AddTextLabelParam() { }
    virtual int id() const = 0;
    virtual const std::string& name() const = 0;
    virtual HudTextLabel* generateTextLabel() const = 0;
};
