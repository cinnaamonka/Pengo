#include "EnemyManager.h"
#include "HitObserver.h"
#include <random> 
#include "EnemyDirectionObserver.h"
#include "CollisionComponent.h"

#pragma warning(disable : 4702)
std::uniform_int_distribution<int> dist(-1, 1);

const auto RANDOM_SIGN = [](int val) { return val == 0 ? -1 : 1; };

std::random_device rd;
std::mt19937 gen(rd());

EnemyManager::EnemyManager(int enemiesAmount, std::vector<glm::vec3>& positions, GameEngine::Scene* scene)
{
	for (int i = 0; i < enemiesAmount; ++i)
	{
		auto enemyActor = EnemyActor::CreateEnemy(positions[i], i);
		m_EnemiesCollisionHitInfoChanged.Attach(enemyActor->GetComponent<HitObserver>());
		m_EnemyDirectionChanged.Attach(enemyActor->GetComponent<EnemyDirectionObserver>());
		m_EnemiesRef.push_back(enemyActor.get());
		scene->Add(std::move(enemyActor));
	}
}

void EnemyManager::CheckEnemiesCollision(std::vector<GameEngine::GameObject*> blocks)
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		for (int j = 0; j < blocks.size(); ++j)
		{
			if (blocks[j]->GetComponent<CollisionComponent>()->IsColliding(m_EnemiesRef[i], hitInfo))
			{
				glm::vec3 direction = {};
				m_EnemiesRef[i]->GetComponent<GameEngine::BlackboardComponent>()->GetData("MovementDirection", direction);

				const bool isMovingRight = direction.x > 0;
				const bool isMovingDown = direction.y > 0;
				const bool isMovingLeft = direction.x < 0;
				const bool isMovingUp = direction.y < 0;

				const int randDirection = RANDOM_SIGN(dist(gen));

				if ((isMovingRight && hitInfo.normal.y == 0) || (isMovingLeft && hitInfo.normal.x == -1))
				{
					HandleMovement(hitInfo, blocks, j, i, randDirection, true);
					return;
				}

				if ((isMovingDown && hitInfo.normal.x == 0) || (isMovingUp && hitInfo.normal.y == -1))
				{
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


void EnemyManager::HandleBorderCollision(GameEngine::GameObject* border)
{
	GameEngine::HitInfo hitInfo;
	const auto borderCollisionComponent = border->GetComponent<CollisionComponent>();

	for (int i = 0; i < m_EnemiesRef.size(); ++i)
	{
		if (!borderCollisionComponent->IsColliding(m_EnemiesRef[i], hitInfo)) continue;

		glm::vec3 direction;
		m_EnemiesRef[i]->GetComponent<GameEngine::BlackboardComponent>()->GetData("MovementDirection", direction);

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
