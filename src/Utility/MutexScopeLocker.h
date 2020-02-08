#pragma once

#include <KYEngine/Utility/Mutex.h>

class MutexScopeLocker
{
public:
    MutexScopeLocker(Mutex& mutex);
    virtual ~MutexScopeLocker();
    
private:
    Mutex& m_mutex;
};