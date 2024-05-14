#include "EnemyManager.h"
#include "HitObserver.h"
#include <random> 
#include "EnemyDirectionObserver.h"
#include "CollisionComponent.h"
#include "BaseBlock.h"
#include <TransformComponent.h>
#include <ActorComponent.h>
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
	for (int i = 0; i < enemiesAmount; ++i)
	{
		auto enemyActor = EnemyActor::CreateEnemy(positions[i], i);
		m_EnemiesCollisionHitInfoChanged.Attach(enemyActor->GetComponent<HitObserver>());
		m_EnemyDirectionChanged.Attach(enemyActor->GetComponent<EnemyDirectionObserver>());
		enemyActor->GetComponent<EnemyActor>()->SetActor(actor);
		enemyActor->GetComponent<EnemyActor>()->HandleInput(&enemyPatrolState);
		m_EnemiesRef.push_back(enemyActor.get());
		scene->Add(std::move(enemyActor));
	}
}

void EnemyManager::CheckEnemiesCollision(std::vector<GameEngine::GameObject*> blocks, GameEngine::Subject<BlockCollisionInfo>* subject,
	int m_PushBlockIndex)
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		for (int j = 0; j < blocks.size(); ++j)
		{
			if (blocks[j]->IsDestroyed() || blocks[j]->GetComponentsAmount() > 100) continue;

			if (blocks[j]->GetComponent<CollisionComponent>()->IsColliding(m_EnemiesRef[i], hitInfo))
			{
				if (i == m_KilledEnemyIndex && j != m_PushBlockIndex) 
				{
					KillEnemy(m_KilledEnemyIndex);
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
					if (blocks[j]->GetComponent<BaseBlock>()->GetIsBreakable() && j != m_PushBlockIndex && !m_EnemiesRef[i]->GetComponent<EnemyActor>()->GetIsKilled())
					{
						blocks[j]->GetComponent<GameEngine::AnimationComponent>()->SetIsDestroyed(true);
						subject->Detach(blocks[j]->GetComponent<BlockObserver>());
					}

					HandleMovement(hitInfo, blocks, j, i, randDirection, true);
					return;
				}

				if ((isMovingDown && hitInfo.normal.x == 0) || (isMovingUp && hitInfo.normal.y == -1))
				{
					if (blocks[j]->GetComponent<BaseBlock>()->GetIsBreakable() && j != m_PushBlockIndex && !m_EnemiesRef[i]->GetComponent<EnemyActor>()->GetIsKilled())
					{
						blocks[j]->GetComponent<GameEngine::AnimationComponent>()->SetIsDestroyed(true);
						subject->Detach(blocks[j]->GetComponent<BlockObserver>());
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
		if (currentBlockIndex == j || blocks[j]->IsDestroyed()) continue;

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

}


void EnemyManager::HandleBorderCollision(GameEngine::GameObject* border)
{
	GameEngine::HitInfo hitInfo;
	const auto borderCollisionComponent = border->GetComponent<CollisionComponent>();

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		if (m_EnemiesRef[i]->IsDestroyed())continue;
		if (!borderCollisionComponent->IsColliding(m_EnemiesRef[i], hitInfo)) continue;

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
		if (block->IsDestroyed())continue;

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

void EnemyManager::CheckCollisionWithPlayer(const glm::vec3& pos)
{
	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		const auto currentEnemyPosition = m_EnemiesRef[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

		if (GameEngine::AreNear(pos, currentEnemyPosition, 5.0f)) 
		{
			m_EnemiesRef[i]->GetComponent<EnemyActor>()->KillPlayer();
			m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(glm::vec3{ 0.0f,0.0f,0.0f });
			return;
		}

		const auto distance = glm::distance(pos, currentEnemyPosition);

		const auto newDirection = pos - currentEnemyPosition;

		if (distance < m_Radius && GameEngine::AreOnSameLine({ 0,0,0 }, pos, currentEnemyPosition))
		{
			m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetIsChasing(true);
			m_EnemiesRef[i]->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(newDirection);
		}
	}
}

