#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

Enemy::Enemy(int x, int y, ENEMY_TYPES type) : position(x, y), collider(nullptr), type(type)
{}

Enemy::~Enemy()
{
	if(collider != nullptr)
		App->collisions->EraseCollider(collider);
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw()
{
	if(collider != nullptr)
		collider->SetPos(position.x + x_collider_correction, position.y + y_collider_correction);

	App->render->Blit(tex, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::SetPath(Path* mov){
	path = mov;
}
