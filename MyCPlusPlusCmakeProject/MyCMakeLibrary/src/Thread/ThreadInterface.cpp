#include <assert.h>
#include "Thread/ThreadInterface.h"
#include <Windows.h>

#define filename "Thread_"

const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)

typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;

#pragma pack(pop)

void SetThreadName(DWORD dwThreadID, const char* threadName) {
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = threadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;

#pragma warning(push)
#pragma warning(disable: 6320 6322)

    __try {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
    }
#pragma warning(pop)
}

PSMMain::ThreadInterface::ThreadInterface() :
    sthread(nullptr),
    isAlive(true),
    threadName("unknown.th")
{
}

PSMMain::ThreadInterface::~ThreadInterface()
{
    shutdown();
}

void runThread(PSMMain::ThreadInterface* threadInst,
    const char* threadName)
{
    assert(threadName);
    assert(threadInst);
    // set thread name
    SetThreadName((DWORD)-1, threadName);
    threadInst->run();
}

void runThreadParam(PSMMain::ThreadInterface* threadInst,
    const char* threadName,
    void* param)
{
    assert(threadName);
    assert(threadInst);
    // set thread name
    SetThreadName((DWORD)-1, threadName);
    threadInst->run(param);
}

void PSMMain::ThreadInterface::shutdown()
{
    isAlive = false;
    if (sthread)
    {
        sthread->join();
        delete sthread;
        sthread = 0;
    }
}

bool PSMMain::ThreadInterface::isShutdown() const
{
    return !isAlive;
}

bool PSMMain::ThreadInterface::init(const char* pThreadName)
{
    assert(pThreadName);
    threadName = pThreadName;
    sthread = new std::thread(runThread,
        this,
        this->threadName.c_str());
    return sthread;
}

bool PSMMain::ThreadInterface::init(const char* pThreadName, void* param)
{
    assert(pThreadName);
    threadName = pThreadName;
    sthread = new std::thread(runThreadParam,
        this,
        this->threadName.c_str(),
        param);
    return sthread;
}

void PSMMain::ThreadInterface::run()
{

}

void PSMMain::ThreadInterface::run(void* param)
{

}
