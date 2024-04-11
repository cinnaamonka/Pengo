#pragma once
#include <BaseComponent.h>
#include <IObserver.h>
#include <Helpers.h>

class GameObject;

class HitObserver : public GameEngine::BaseComponent, public GameEngine::IObserver<GameEngine::HitInfo>
{
public:

	HitObserver(GameEngine::GameObject* pGameObject);
	~HitObserver() = default;
	HitObserver(const HitObserver& other) = delete;
	HitObserver& operator=(const HitObserver& other) = delete;
	HitObserver(HitObserver&& other) = delete;

	void Notify(const GameEngine::HitInfo& message_from_subject) override;

private:
	void ResetHorizontalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo);
	void ResetVerticalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo);

};

