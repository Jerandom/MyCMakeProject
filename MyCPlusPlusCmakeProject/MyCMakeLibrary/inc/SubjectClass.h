#pragma once

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include "Observer/Subject.h"
#include "ObserverClass.h"

class MAINDLL_API SubjectClass : 
	public SingletonClass<SubjectClass>,
	public Subject<int, SObserverClass>
{
	friend class SingletonClass<SubjectClass>;

public:
	void attachSubjectObserver(ObserverClass* pObserver);
	void detachSubjectObserver(ObserverClass* pObserver);
	void notifySubjectEvent(int EventId, SObserverClass sObserverClass);
	void notifySubjectEventWArgs(int EventId, SObserverClass sObserverClass, int i);

protected:
	SubjectClass();
	~SubjectClass();
};