#pragma once

#include <pthread.h>
#include <stdexcept>

class Mutex
{
public:
    Mutex(bool recursive = false);
    virtual ~Mutex();

private:
    Mutex(const Mutex& other) { throw std::runtime_error("Cannot copy Mutex"); }
    
public:
    void lock();
    bool tryLock(); // return true if you adquire the mutex
    void unlock();
    
private:
    pthread_mutex_t m_mutex;
};

class RecursiveMutex
    : public Mutex
{
public:
    RecursiveMutex(): Mutex(true) { }
};