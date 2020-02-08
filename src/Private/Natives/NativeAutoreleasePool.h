#pragma once

class NativeAutoreleasePool
{
public:
    NativeAutoreleasePool();
    virtual ~NativeAutoreleasePool();
private:
    void* m_pool;
};