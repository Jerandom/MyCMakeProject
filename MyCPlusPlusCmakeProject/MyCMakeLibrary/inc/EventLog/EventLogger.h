#ifndef _EVENT_LOGGER_H
#define _EVENT_LOGGER_H

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include "Thread/ThreadInterface.h"

class MAINDLL_API EventLogger : 
    public SingletonClass<EventLogger>,
    public ThreadInterface
{
    friend class SingletonClass<EventLogger>;

protected:
    EventLogger();
    virtual ~EventLogger();

public:

private:
    
}

#endif //_EVENT_LOG_H