#pragma once

#include <string>

class RawData
{
public:
    virtual ~RawData() { }
    virtual const std::string& name() const = 0;
    virtual void* data() = 0;
};