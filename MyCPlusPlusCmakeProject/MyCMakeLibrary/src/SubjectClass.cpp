#include "SubjectClass.h"

SubjectClass::SubjectClass() :
	SingletonClass<SubjectClass>(),
	Subject<int, SObserverClass>()
{
}

SubjectClass::~SubjectClass()
{
}

void SubjectClass::attachSubjectObserver(ObserverClass* pObserver)
{
	attachObserver(pObserver);
}

void SubjectClass::detachSubjectObserver(ObserverClass* pObserver)
{
	detachObserver(pObserver);
}

void SubjectClass::notifySubjectEvent(int EventId, SObserverClass sObserverClass)
{
	notifyEvent(EventId, sObserverClass);
}

void SubjectClass::notifySubjectEventWArgs(int EventId, SObserverClass sObserverClass, int i)
{
	notifyEventWArgs(EventId, sObserverClass, i);
}
