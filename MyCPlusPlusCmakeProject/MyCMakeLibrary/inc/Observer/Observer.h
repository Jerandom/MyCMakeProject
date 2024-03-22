#ifndef _OBSERVER_H
#define _OBSERVER_H

#include "MainAPI/MainAPI.h"
#include <string>

template<typename... Args>
class MAINDLL_API Observer
{
public:
    virtual void notifyEvent(Args... args) = 0;

    /* Need to predefine data type for the argument as virtual is not compatible with template
              data type for the argument needs to be the same as the observer class 
                 E.g If you are taking in an int, need to predefine int here */

    virtual void notifyEventWArgs(Args... args, int i) {};
};

#endif //_QR_OBSERVER_H
