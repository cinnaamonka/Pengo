#include "Subject.h"
#include "Observer.h"

namespace GameEngine
{
	void Subject::AddObserver(std::unique_ptr<Observer> pObserver)
	{
		m_pObservers.push_back(std::move(pObserver));
	}

	void Subject::RemoveObserver(std::unique_ptr<Observer> pObserver) 
	{
		m_pObservers.remove_if([&pObserver](const auto& observer) 
			{
			return observer.get() == pObserver.get();
			});
	}
	void Subject::OnNotify(GameObject* obj, Event event) const
	{
		for (const auto& observer : m_pObservers) 
		{
			observer->OnNotify(event,obj);
		}
	}
}