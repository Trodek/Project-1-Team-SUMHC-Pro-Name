#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y), collider(nullptr)
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
		collider->SetPos(position.x, position.y);

	App->render->Blit(tex, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::SetPath(Path* mov){
	path = mov;
}
