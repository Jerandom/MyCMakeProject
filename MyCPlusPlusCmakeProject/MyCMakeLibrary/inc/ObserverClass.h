#include "MainAPI/MainAPI.h"
#include "Observer/Observer.h"

struct SObserverClass
{
	std::string message;
};

class MAINDLL_API ObserverClass : 
	public Observer<int, SObserverClass>
{
public:
	//declare the event type for function
	enum EventType 
	{
		UpdateMessage,
		UpdateAction,
	};

	void notifyEvent(int EventId, SObserverClass sObserverClass) override;

	void notifyEventWArgs(int EventId, SObserverClass sObserverClass, int i) override;
};