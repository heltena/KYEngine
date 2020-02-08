#include <KYEngine/Utility/MutexScopeLocker.h>

MutexScopeLocker::MutexScopeLocker(Mutex& mutex)
    : m_mutex(mutex)
{
    m_mutex.lock();
}

MutexScopeLocker::~MutexScopeLocker()
{
    m_mutex.unlock();
}