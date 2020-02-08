#pragma once

#include <KYEngine/Utility/Box.h>
#include <string>

class Font
{
public:
    virtual ~Font() { }
    virtual const std::string& name() const = 0;
	virtual const void* internalData() const = 0;
    virtual const void* internalBorderData() const = 0;
	virtual double faceSize() const = 0;
    virtual bool hasBorder() const = 0;
    virtual double borderOutset() const = 0;
};
