#include "CMakeLibrary.h"

#include <iostream>

CMakeLibrary::CMakeLibrary() :
	SingletonClass<CMakeLibrary>()
{
	std::cout << "Hello CMake Library" << std::endl;

	SubjectClass::instance().attachSubjectObserver(&observerClass);

	SubjectClass::instance().notifySubjectEvent(1, sObserverClass);
}

CMakeLibrary::~CMakeLibrary()
{
}
