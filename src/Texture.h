#pragma once

#include <string>

class Texture
{
protected:
    virtual ~Texture() { }
public:
    virtual const std::string& name() const = 0;
	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual void bind() = 0;
};