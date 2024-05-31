#include "EnemyManager.h"
#include "HitObserver.h"
#include <random> 
#include "EnemyDirectionObserver.h"
#include "CollisionComponent.h"
#include "BaseBlock.h"
#include <HealthObserver.h>
#include <TransformComponent.h>
#include <ActorComponent.h>
#include <AnimationComponent.h>
#include <SoundServiceLocator.h>
#include <TimeManager.h>
#include "Structs.h"
#include <HUD.h>
#include <TimeManager.h>

#include <Helpers.h>

#pragma warning(disable : 4702)
std::uniform_int_distribution<int> dist(-1, 1);

const auto RANDOM_SIGN = [](int val) { return val == 0 ? -1 : 1; };

std::random_device rd;
std::mt19937 gen(rd());

EnemyPatrolState EnemyManager::enemyPatrolState = EnemyPatrolState();
EnemyDyingState EnemyManager::enemyDyingState = EnemyDyingState();

EnemyManager::EnemyManager(int enemiesAmount, std::vector<glm::vec3>& positions, GameEngine::Scene* scene, GameEngine::GameObject* actor) :
	m_KilledEnemyIndex(-1)
{
	m_pSceneRef = scene;

	for (int i = 0; i < enemiesAmount; ++i)
	{
		SpawnEnemy(positions[i]);
		
	}
	m_pActorComponent = actor->GetComponent<GameEngine::ActorComponent>(); 
}

void EnemyManager::CheckEnemiesCollision(std::vector<GameEngine::GameObject*>& blocks, int& m_PushBlockIndex,
	GameEngine::Subject<EventInfo>* eventSubject, GameEngine::Subject<Score>* scoreSubject, GameEngine::Subject<GameEngine::HUDEvent>* hudSubject)
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		for (int j = 0; j < blocks.size(); ++j)
		{
			if (blocks[j]->GetComponent<CollisionComponent>()->IsColliding(m_EnemiesRef[i], hitInfo))
			{
				if (i == m_KilledEnemyIndex && m_PushBlockIndex == -1)
				{
					scoreSubject->CreateMessage(Score{ ScoreType::EnemyKilled,m_EnemiesRef[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition() });
					hudSubject->CreateMessage(GameEngine::HUDEvent::InceaseScore500);
					KillEnemy(m_KilledEnemyIndex);
					hudSubject->CreateMessage(GameEngine::HUDEvent::DecreaseSnoBeesAmount);
					eventSubject->CreateMessage(EventInfo{ Event::EnemySpawnFromEggBlock });
					return;
				}
				glm::vec3 direction = m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->GetMovementDirection();

				const bool isMovingRight = direction.x > 0;
				const bool isMovingDown = direction.y > 0;
				const bool isMovingLeft = direction.x < 0;
				const bool isMovingUp = direction.y < 0;

				const int randDirection = RANDOM_SIGN(dist(gen));

				if ((isMovingRight && hitInfo.normal.y == 0) || (isMovingLeft && hitInfo.normal.x == -1))
				{
					if (!m_EnemiesRef[i]->GetComponent<EnemyActor>()->GetIsKilled() && !blocks[j]->GetComponent<BaseBlock>()->GetContainsEggs())
					{
						const EventInfo eventInfo
						{
							Event::BlockDestroyed,j
						};

						eventSubject->CreateMessage(eventInfo);
					}

					HandleMovement(hitInfo, blocks, j, i, randDirection, true);
					return;
				}

				if ((isMovingDown && hitInfo.normal.x == 0) || (isMovingUp && hitInfo.normal.y == -1))
				{
					if (!m_EnemiesRef[i]->GetComponent<EnemyActor>()->GetIsKilled() && !blocks[j]->GetComponent<BaseBlock>()->GetContainsEggs())
					{
						const EventInfo eventInfo
						{
							Event::BlockDestroyed,j
						};

						eventSubject->CreateMessage(eventInfo);
					}

					HandleMovement(hitInfo, blocks, j, i, randDirection, false);

					return;
				}
			}

		}
	}
}
void EnemyManager::HandleMovement(GameEngine::HitInfo& hitInfo, std::vector<GameEngine::GameObject*> blocks, int currentBlockIndex, int currentEnemyIndex, const int randDirection, bool isHorizontal)
{
	for (int j = 0; j < static_cast<int>(blocks.size()); ++j)
	{
		if (currentBlockIndex == j) continue;

		if ((isHorizontal && blocks[j]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_EnemiesRef[currentEnemyIndex], hitInfo)) ||
			(!isHorizontal && blocks[j]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_EnemiesRef[currentEnemyIndex], hitInfo)))
		{
			CreateMessage(GameEngine::EnemyInfo{ currentEnemyIndex, isHorizontal ? glm::vec3(-hitInfo.normal.x, 0, 0) : glm::vec3(0, -hitInfo.normal.y, 0) });

			continue;
		}
	}

	CreateMessage(GameEngine::EnemyInfo{ currentEnemyIndex, !isHorizontal ? glm::vec3(randDirection, 0, 0) : glm::vec3(0, randDirection, 0) });
	return;
}

void EnemyManager::KillEnemy(int index)
{
	m_EnemiesRef[index]->GetComponent<GameEngine::AnimationComponent>()->SetSpeed(0.f);
	m_KilledEnemyIndex = -1;
	m_EnemiesRef[index]->GetComponent<EnemyActor>()->HandleInput(&enemyDyingState);
	m_EnemyDirectionChanged.Detach(m_EnemiesRef[index]->GetComponent<EnemyDirectionObserver>());
	m_EnemiesRef.erase(m_EnemiesRef.begin() + index);
	ResetEnemiesIndexes();
	GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::SnowBeeSquashed), 20);

	if(m_EnemiesRef.empty())
	{
		m_pActorComponent->Win(); 
	}
}

void EnemyManager::ResetEnemiesIndexes()
{
	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		m_EnemiesRef[i]->GetComponent<EnemyDirectionObserver>()->SetIndex(i);
	}
}


void EnemyManager::HandleBorderCollision(GameEngine::GameObject* border,GameEngine::Subject<EventInfo>* eventSubject)
{
	GameEngine::HitInfo hitInfo;
	const auto borderCollisionComponent = border->GetComponent<CollisionComponent>();

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		if (!borderCollisionComponent->IsColliding(m_EnemiesRef[i], hitInfo)) continue;

		eventSubject->CreateMessage(EventInfo{ Event::EnemyCollidedWithBorder,i });

		glm::vec3 direction = m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->GetMovementDirection();

		const glm::vec3 up = glm::vec3(0, -1, 0);
		const glm::vec3 down = glm::vec3(0, 1, 0);
		const glm::vec3 right = glm::vec3(1, 0, 0);
		const glm::vec3 left = glm::vec3(-1, 0, 0);

		if (direction.y)
		{
			CreateMessage(GameEngine::EnemyInfo{ i, hitInfo.normal.y < 0 ? up : down });
		}

		if (direction.x)
		{
			CreateMessage(GameEngine::EnemyInfo{ i, hitInfo.normal.x > 0 ? right : left });
		}
	}
}

void EnemyManager::CheckCollisionWithPushedBlock(GameEngine::GameObject* block)
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{

		if (block->GetComponent<CollisionComponent>()->IsColliding(m_EnemiesRef[i], hitInfo))
		{
			glm::vec3 flyingBlockDirection = block->GetComponent<GameEngine::AnimationComponent>()->GetMovementDirection();

			m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetSpeed(10.0f);
			m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(flyingBlockDirection);
			m_EnemiesRef[i]->GetComponent<EnemyActor>()->SetIsKilled(true);

			m_KilledEnemyIndex = i;

		}
	}
}

void EnemyManager::CheckCollisionWithPlayer(std::vector<GameEngine::GameObject*> actors, GameEngine::Subject<GameEngine::HUDEvent>* hudSubject) 
{
	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		for (int j = 0; j < actors.size();++j)
		{
			auto playerPosition = actors[j]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

			const auto currentEnemyPosition = m_EnemiesRef[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

			if (GameEngine::AreNear(playerPosition, currentEnemyPosition, 5.0f))
			{
				m_EnemiesRef[i]->GetComponent<EnemyActor>()->KillPlayer(j);
				m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection({ 0,0,0 });
				m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetSpeed(0.0f);
				hudSubject->CreateMessage(GameEngine::HUDEvent::DecreaseLife);
				KillEnemy(i);
				return;
			}

			const auto distance = glm::distance(playerPosition, currentEnemyPosition);

			const auto newDirection = playerPosition - currentEnemyPosition;

			if (distance < m_Radius && GameEngine::AreOnSameLine({ 0,0,0 }, playerPosition, currentEnemyPosition))
			{
				m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetIsChasing(true);
				m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(newDirection);

			}
		}
		
	}
}

void EnemyManager::SpawnEnemy(const glm::vec3& pos)
{
	int enemiesAmount = static_cast<int>(m_EnemiesRef.size());

	auto enemyActor = EnemyActor::CreateEnemy(pos, enemiesAmount);
	m_EnemiesCollisionHitInfoChanged.Attach(enemyActor->GetComponent<HitObserver>());
	m_EnemyDirectionChanged.Attach(enemyActor->GetComponent<EnemyDirectionObserver>());
	enemyActor->GetComponent<EnemyActor>()->HandleInput(&enemyPatrolState);
	m_EnemiesRef.push_back(enemyActor.get());
	m_pSceneRef->Add(std::move(enemyActor));
}

void EnemyManager::CheckEnemiesCollectionSize(GameEngine::Subject<GameEngine::HUDEvent>* hudSubject)
{
	if (m_EnemiesRef.empty())
	{
		if (GameEngine::TimeManager::GetInstance().IsTimerElapsed("StartTimer"))
		{
			hudSubject->CreateMessage(GameEngine::HUDEvent::IncreaseScore30);
			
		}
		
	}
}

void EnemyManager::AddPlayer(GameEngine::GameObject* actor)
{
	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		m_EnemiesRef[i]->GetComponent<EnemyActor>()->SetActor(actor); 
	}
}

