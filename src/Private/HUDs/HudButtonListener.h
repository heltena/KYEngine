#pragma once

class HudButtonListener
{
public:
    virtual void hudButtonPressed(int id) = 0;
    virtual void hudButtonReleased(int id) = 0;
};