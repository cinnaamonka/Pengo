#pragma once
#include "memory"
#include <GameObject.h>
#include <BaseComponent.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <IObserver.h>

enum class Event
{
	BlockIndexesChanged,
	BlockDestroyed
};
struct EventInfo
{
	Event event;
	int index = 1;

	EventInfo(Event event, int index = 1) : event(event), index(index) {};
	EventInfo() {};
};
class EnvironmentObserver final:public GameEngine::BaseComponent, public GameEngine::IObserver<EventInfo>
{
	public:
	EnvironmentObserver(GameEngine::GameObject* pGameObject) ; 
	~EnvironmentObserver() = default; 

	EnvironmentObserver(const EnvironmentObserver& other) = delete; 
	EnvironmentObserver(EnvironmentObserver&& other) = delete;
	EnvironmentObserver& operator=(const EnvironmentObserver& other) = delete; 
	EnvironmentObserver& operator=(EnvironmentObserver&& other) = delete; 

	void Notify(const EventInfo& event) override; 
};

