#ifndef _THREAD_INTERFACE_H
#define _THREAD_INTERFACE_H

#include <thread>
#include <memory>
#include <string>

class ThreadInterface
{
public:
    ThreadInterface();
    virtual ~ThreadInterface();

    virtual void shutdown();
    bool isShutdown() const;
    bool init(const char* pThreadName);
    bool init(const char* pThreadName, void* param);
    virtual void run(void);
    virtual void run(void* param);

private:
    std::thread* sthread;
    bool isAlive;
    std::string threadName;
};

#endif