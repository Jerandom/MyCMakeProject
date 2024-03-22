/*
 * Singleton.h
 *
 *  Created on: Aug 29, 2019
 *      Author: irvin
 */

#ifndef SINGLETONCLASS_H_
#define SINGLETONCLASS_H_

template <typename T>
class SingletonClass
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
