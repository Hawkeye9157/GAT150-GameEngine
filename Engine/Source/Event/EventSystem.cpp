#include "EventSystem.h"

void EventSystem::AddObserver(const id_t& id, Observer* observer, EventHandler* eHandler)
{
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eHandler = eHandler;

	m_dispatchers[id].push_back(dispatcher);
}

void EventSystem::Notify(const Event& event)
{
	//searches for key
	auto iter = m_dispatchers.find(event.id);
	//checks if key was found
	if (iter != m_dispatchers.end()) {
		//get list of dispatchers
		auto dispatchers = iter->second;

		for (auto& dispatcher : dispatchers) {
			dispatcher.eHandler(event);
		}
	}
}
