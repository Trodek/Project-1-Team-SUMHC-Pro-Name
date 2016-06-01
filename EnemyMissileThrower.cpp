#include "Application.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "EnemyMissileThrower.h"

EnemyMissileThrower::EnemyMissileThrower(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
	position.x = x;
	position.y = y;

	original = position;

	Idle.PushBack({ 0, 0, 56, 48 });
	Idle.PushBack({ 56, 0, 56, 48 });
	Idle.speed = 0.4f;

	tex = App->particles->missilethrower;
	missile = &App->particles->missile2;

	hp = 24;
	points = 150;

	collider = App->collisions->AddCollider({ 0, 0, 50, 40 }, COLLIDER_ENEMY, (Module*)App->enemies);

	dead = &App->particles->green_basic_dead;

}

void EnemyMissileThrower::Draw(){
	position = original + path->GetCurrentSpeed();
	collider->SetPos(position.x, position.y);
	App->render->Blit(tex, position.x, position.y, &Idle.GetCurrentFrame());
}

void EnemyMissileThrower::Shot(){
	if (cont++ % 60 == 0){
		App->particles->SetColliderCorrection(missile, 0, 16);
		App->particles->AddParticle(*missile, position.x - 1, position.y + 8, COLLIDER_ENEMY_SHOT, { 0, 0, 16, 16 });
		App->particles->AddParticle(*missile, position.x + 37, position.y + 8, COLLIDER_ENEMY_SHOT, { 0, 0, 16, 16 });
	}
}