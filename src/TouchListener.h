#pragma once

#include <KYEngine/Touch.h>

#include <map>

class TouchListener
{
public:
	virtual void touchesBegan(const std::map<int, Touch>& touches) = 0;
	virtual void touchesMoved(const std::map<int, Touch>& touches) = 0;
	virtual void touchesEnded(const std::map<int, Touch>& touches) = 0;
    virtual void touchesCancelled(const std::map<int, Touch>& touches) = 0;
};