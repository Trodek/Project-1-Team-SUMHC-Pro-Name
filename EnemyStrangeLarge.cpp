#include "Application.h"
#include "ModuleCollision.h"
#include "EnemyStrangeLarge.h"
#include "ModuleParticles.h"

EnemyStrangeLarge::EnemyStrangeLarge(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types) {
	original.x = x;
	original.y = y;

	position.x = x;
	position.y = y;

	Idle.PushBack({ 0, 0, 115, 40 });

	animation = &Idle;

	hp = 54;
	points = 1500;

	collider = App->collisions->AddCollider({ 0, 0, 115, 40 }, COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);

	blaster = &App->particles->enemy_blaster;
	shot = &App->particles->enemy_shot_especial;

	tex = App->particles->strange_large;

	dead = &App->particles->truck_dead;

}

void EnemyStrangeLarge::Shot(){
	if (cont % 179 == 0){
		if (cont % 2 == 0){
			App->particles->AddParticle(*blaster, position.x + 1, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 40 });
			App->particles->AddParticle(*blaster, position.x + 100, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 40 });
		}
		else{
			App->particles->SetParticleSpeed(shot, 0, 2);
			App->particles->AddParticle(App->particles->green_basic_bullet_start, position.x + 77, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			App->particles->AddParticle(App->particles->green_basic_bullet_start, position.x + 25, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			App->particles->AddParticle(*shot, position.x + 25, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 14, 15 });
			App->particles->AddParticle(*shot, position.x + 77, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 14, 15 });
			App->particles->SetParticleSpeed(shot, 1, 2);
			App->particles->AddParticle(*shot, position.x + 25, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 14, 15 });
			App->particles->AddParticle(*shot, position.x + 77, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 14, 15 });
			App->particles->SetParticleSpeed(shot, -1, 2);
			App->particles->AddParticle(*shot, position.x + 25, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 14, 15 });
			App->particles->AddParticle(*shot, position.x + 77, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 14, 15 });
		}
	}

	cont++;
	position = original + path->GetCurrentSpeed();

}