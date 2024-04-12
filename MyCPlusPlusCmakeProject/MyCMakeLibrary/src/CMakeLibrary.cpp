#include "CMakeLibrary.h"

#include <iostream>

CMakeLibrary::CMakeLibrary() :
	SingletonClass<CMakeLibrary>()
{
	SubjectClass::instance().attachSubjectObserver(&observerClass);
	SubjectClass::instance().notifySubjectEvent((int)ObserverClass::EventType::UpdateMessage, sObserverClass);
}

CMakeLibrary::~CMakeLibrary()
{
}
