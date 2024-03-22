#include "ObserverClass.h"

#include <iostream>

void ObserverClass::notifyEvent(int EventId, SObserverClass sObserverClass)
{
	EventType eType = static_cast<EventType>(EventId);

	switch (eType)
	{
	case EventType::UpdateMessage:
		std::cout << "Type 1: " << sObserverClass.message<< "   " << this << std::endl;
		break;
	case EventType::UpdateAction:
		std::cout << "Type 2: " << sObserverClass.message<< "   " << this << std::endl;
		break;
	}
}

void ObserverClass::notifyEventWArgs(int EventId, SObserverClass sObserverClass, int i)
{
	std::cout << "I am another parameter " << i << "   " << this << std::endl;
}

