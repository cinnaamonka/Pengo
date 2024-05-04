#include "EnemyManager.h"
#include "HitObserver.h"
#include <random> 
#include "EnemyDirectionObserver.h"
#include "CollisionComponent.h"

std::uniform_int_distribution<int> dist(-1, 1);

const auto RANDOM_SIGN = [](int val) { return val == 0 ? -1 : 1; };

std::random_device rd;
std::mt19937 gen(rd());

EnemyManager::EnemyManager(int enemiesAmount)
{
	for (int i = 0; i < enemiesAmount; ++i)
	{
		auto enemyActor = EnemyActor::CreateEnemy(); 
		m_EnemiesCollisionHitInfoChanged.Attach(enemyActor->GetComponent<HitObserver>());
		m_EnemyDirectionChanged.Attach(enemyActor->GetComponent<EnemyDirectionObserver>());
		m_EnemiesRef.push_back(enemyActor.get());
		m_pEnemies.push_back(std::move(enemyActor));
	}

}

bool EnemyManager::CheckEnemiesCollision(GameEngine::HitInfo& hitInfo,int, int currentBlockIndex,
	std::vector<GameEngine::GameObject*> blocks)
{
    // NEW FEATURE SHITTY CODE
    if (blocks[currentBlockIndex]->GetComponent<CollisionComponent>()->IsColliding(m_EnemiesRef[0], hitInfo))
    {
        glm::vec3 direction = {};

        m_EnemiesRef[0]->GetComponent<GameEngine::BlackboardComponent>()->GetData("MovementDirection", direction);

        const bool isMovingRight = direction.x > 0;
        const bool isMovingDown = direction.y > 0;
        const bool isMovingLeft = direction.x < 0;
        const bool isMovingUp = direction.y < 0;

        const int randDirection = RANDOM_SIGN(dist(gen));


        if (isMovingRight && hitInfo.normal.y == 0)
        {
            for (int j = 0; j < static_cast<int>(blocks.size()); ++j)
            {
                if (currentBlockIndex == j) continue;

                if (blocks[j]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_EnemiesRef[0], hitInfo))
                {
                    CreateMessage(glm::vec3(0, -hitInfo.normal.y, 0));

                    return true;
                }
            }

            CreateMessage(glm::vec3(0, randDirection, 0));

            return true;
        }

        if (isMovingDown && hitInfo.normal.x == 0)
        {
            for (int j = 0; j < static_cast<int>(blocks.size()); ++j)
            {
                if (currentBlockIndex == j) continue;

                if (blocks[j]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_EnemiesRef[0], hitInfo))
                {
                    CreateMessage(glm::vec3(-hitInfo.normal.x, 0, 0));

                    return true;
                }
            }

            CreateMessage(glm::vec3(randDirection, 0, 0));

            return true;
        }

        if (isMovingUp && hitInfo.normal.y == -1)
        {
            for (int j = 0; j < static_cast<int>(blocks.size()); ++j)
            {
                if (currentBlockIndex == j) continue;

                if (blocks[j]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_EnemiesRef[0], hitInfo))
                {
                    CreateMessage(glm::vec3(-hitInfo.normal.x, 0, 0));

                    return true;
                }
            }

            CreateMessage(glm::vec3(randDirection, 0, 0));

            return true;
        }

        if (isMovingLeft && hitInfo.normal.x == -1)
        {
            for (int j = 0; j < static_cast<int>(blocks.size()); ++j)
            {
                if (currentBlockIndex == j) continue;

                if (blocks[j]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_EnemiesRef[0], hitInfo))
                {
                    CreateMessage(glm::vec3(0, -hitInfo.normal.y, 0));

                    return true;
                }
            }

            CreateMessage(glm::vec3(0, randDirection, 0));

            return true;
        }
    }
    return false;
}
