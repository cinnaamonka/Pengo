#include "EnemyActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <ResourceManager.h>
#include <ActorComponent.h>
#include "HitObserver.h"

EnemyActor::EnemyActor():
	Entity("Enemy.tga",glm::vec3{ 200, 300,0 })
{

}
