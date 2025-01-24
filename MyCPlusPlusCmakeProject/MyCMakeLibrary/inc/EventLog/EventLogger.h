#ifndef _EVENT_LOGGER_H
#define _EVENT_LOGGER_H

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include "Thread/ThreadInterface.h"

enum LogMode{
    ERROR,
    DEBUG,
    DEFAULT
}

class MAINDLL_API EventLogger : 
    public SingletonClass<EventLogger>,
{
    friend class SingletonClass<EventLogger>;

protected:
    EventLogger();
    virtual ~EventLogger();

public:
    void log(std::string& fileName, LogMode mode, std::string& message);

private:
    std::string getLogTimestamp();
    std::string getFileTimestamp();
    std::string logModeToString(LogMode mode);
    std::string formatString(std::string& message, ...);
}

#endif //_EVENT_LOGER_H