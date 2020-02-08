#pragma once

#include <string>

class HudProgressView;

class AddProgressViewParam
{
public:
    virtual ~AddProgressViewParam() { }
    virtual int id() const = 0;
    virtual const std::string& name() const = 0;
    virtual HudProgressView* generateProgressView() const = 0;
};
