#include <KYEngine/AsyncWorker.h>

AsyncWorker::AsyncWorker()
{
    m_state = NOTHING;
}

AsyncWorker::~AsyncWorker()
{
    switch(m_state) {
    case NOTHING:
        break;
    case RUNNING:
        join();
        break;
    case FINISHED:
        join();
        break;
    }
}

void AsyncWorker::run(Work* work)
{
    if (m_state == NOTHING) {
        m_state = RUNNING;
        m_work = work;
        pthread_create(&m_thread, NULL, AsyncWorker::pthreadFunc, this);
    }        
}

void AsyncWorker::join()
{
    if (m_state == RUNNING || m_state == FINISHED) {
        pthread_join(m_thread, NULL);
        m_state = NOTHING;
    }
}

void* AsyncWorker::pthreadFunc(void* param)
{
    AsyncWorker* self = (AsyncWorker*)param;
    return self->pthreadFunc();
}

void* AsyncWorker::pthreadFunc()
{
    void* result = m_work->workRun();
    m_state = FINISHED;
    return result;
}