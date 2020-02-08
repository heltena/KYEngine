#pragma once

#include <KYEngine/Work.h>

#include <pthread.h>

class AsyncWorker
{
private:
    enum StateEnum {
        NOTHING,
        RUNNING,
        FINISHED
    };

public:
    AsyncWorker();
    virtual ~AsyncWorker();
    
public:
    void run(Work* work);
    bool isFinished() { return m_state == FINISHED; }
    void join();
  
private:
    static void* pthreadFunc(void* param);
    void* pthreadFunc();

private:
    StateEnum m_state;
    pthread_t m_thread;
    Work* m_work;
};