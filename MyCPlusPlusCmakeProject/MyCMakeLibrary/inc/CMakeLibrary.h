#pragma once

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include "SubjectClass.h"

class MAINDLL_API CMakeLibrary : 
	public SingletonClass<CMakeLibrary>
{
	friend class SingletonClass<CMakeLibrary>;
public:

protected:
	CMakeLibrary();
	~CMakeLibrary();

private:
	ObserverClass observerClass;
	SObserverClass sObserverClass;
};