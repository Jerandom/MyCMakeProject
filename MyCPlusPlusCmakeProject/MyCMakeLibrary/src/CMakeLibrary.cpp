#include "CMakeLibrary.h"

#include <iostream>

CMakeLibrary::CMakeLibrary() :
	SingletonClass<CMakeLibrary>()
{
	std::cout << "Hello CMake Library" << std::endl;

	SubjectClass::instance().attachSubjectObserver(&observerClass);

	SubjectClass::instance().notifySubjectEvent((int)ObserverClass::EventType::UpdateMessage, sObserverClass);
}

CMakeLibrary::~CMakeLibrary()
{
}
