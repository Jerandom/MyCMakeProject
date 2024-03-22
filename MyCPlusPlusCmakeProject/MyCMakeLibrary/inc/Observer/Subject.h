#ifndef _SUBJECT_H
#define _SUBJECT_H

#include "MainAPI/MainAPI.h"
#include "Observer.h"
#include <vector>
#include <iostream>
#include <mutex>
#include <algorithm>

template <typename... Args>
class MAINDLL_API Subject
{
public:
    Subject() {};
    virtual ~Subject() {};

    //for attaching observer with variadic template arguments
    bool attachObserver(Observer<Args...>* pObserver)
    {
        //push back the obj to a vector
        try
        {
            std::lock_guard<std::mutex> lock(mutexObserver);
            if (pObserver != NULL)
            {
                vecObserver.push_back(pObserver);
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    //for detaching observer with variadic template arguments
    bool detachObserver(Observer<Args...>* pObserver)
    {
        //fine and erase the obj from the vector
        try
        {
            std::lock_guard<std::mutex> lock(mutexObserver);
            auto obj = std::find(vecObserver.begin(), vecObserver.end(), pObserver);
            if (obj != vecObserver.end())
            {
                vecObserver.erase(obj);
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    //notify event 1 with variadic template arguments
    void notifyEvent(Args... args)
    {
        //function call using the obj class
        std::lock_guard<std::mutex> lock(mutexObserver);
        for (auto observer : vecObserver)
        {
            observer->notifyEvent(args...);
        }
    }

    //notify event 1 with variadic template arguments
    template<typename AdditionalArg>
    void notifyEventWArgs(Args... args, AdditionalArg additionalArg)
    {
        //function call using the obj class with additional argument
        std::lock_guard<std::mutex> lock(mutexObserver);
        for (auto observer : vecObserver)
        {
            observer->notifyEventWArgs(args..., additionalArg);
        }
    }

private:
    std::vector<Observer<Args...>*> vecObserver;
    std::mutex mutexObserver;
};

#endif //_QR_SUBJECT_H
