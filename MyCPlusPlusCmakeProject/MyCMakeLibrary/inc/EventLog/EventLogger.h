#ifndef _EVENT_LOGGER_H
#define _EVENT_LOGGER_H

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include "Thread/ThreadInterface.h"

enum LogPriority{
    SERVERE,
    NORMAL,
    LOW
}

class MAINDLL_API EventLogger : 
    public SingletonClass<EventLogger>,
    public ThreadInterface
{
    friend class SingletonClass<EventLogger>;

protected:
    EventLogger();
    virtual ~EventLogger();

public:
    void log(std::string& fileName, LogPriority priority, std::string& message);

private:
    std::string getLogTimestamp();
    std::string getFileTimestamp();
    std::string priorityToString(LogPriority priority);

    void run() override;
    
}

#endif //_EVENT_LOGER_H