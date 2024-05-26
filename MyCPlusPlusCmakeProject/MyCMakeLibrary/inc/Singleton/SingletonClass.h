#ifndef SINGLETONCLASS_H_
#define SINGLETONCLASS_H_

#include "MainAPI/MainAPI.h"

template <typename T>
class MAINDLL_API SingletonClass
{
public:
    static T& instance();

    virtual bool init(void) { return true; };

    SingletonClass(SingletonClass const&) = delete;             // Copy construct
    SingletonClass(SingletonClass&&) = delete;                  // Move construct
    SingletonClass& operator=(SingletonClass const&) = delete;  // Copy assign
    SingletonClass& operator=(SingletonClass&&) = delete;      // Move assign

protected:
    SingletonClass() {};
    ~SingletonClass() {};

    static T* SingletonInstance;
};

#endif /* SINGLETONCLASS_H_ */
