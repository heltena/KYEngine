#include <KYEngine/Utility/Mutex.h>
#include <errno.h>

Mutex::Mutex(bool recursive)
{
    if (recursive) {
        pthread_mutexattr_t attr;
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &attr);
    } else
        pthread_mutex_init(&m_mutex, NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock()
{
    pthread_mutex_lock(&m_mutex);
}

bool Mutex::tryLock()
{
    return pthread_mutex_trylock(&m_mutex) != EBUSY;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&m_mutex);
}