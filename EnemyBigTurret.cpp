#include "Application.h"
#include "ModulePlayer.h"
#include "EnemyBigTurret.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL_timer.h"

#define nullrect {0,0,0,0} 
#define shot_box {0,0,14,14}

EnemyBigTurret::EnemyBigTurret(int x, int y) : Enemy(x, y)
{
	idle.PushBack({ 16, 24, 63, 64 });

	tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Big Turret/big turret.png");

	collider = App->collisions->AddCollider({ 0, 0, 63, 64 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &idle;

	hp = 60;
	points = 810;
}

void EnemyBigTurret::UpdateAnim()
{
	
}

void EnemyBigTurret::Shot(){

	now = SDL_GetTicks();

	Particle* turret_bullet = &App->particles->big_turret_bullet;
	Particle* turret_bullet2 = &App->particles->big_turret_bullet;
	Particle* turret_bullet3 = &App->particles->big_turret_bullet;
	Particle* shoot_start = &App->particles->big_turret_bullet_start;

	if (hp>0){
		if (now - last_shot > 400){
			App->particles->SetParticleSpeed(turret_bullet, 3.53f, 2.0f);
			App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet->collider, shot_box, 135);
			App->particles->SetParticleSpeed(turret_bullet, 3.53f, 3.5f);
			App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet2->collider, shot_box, 135, 0.9);
			App->particles->SetParticleSpeed(turret_bullet, 3.53f, 4.5f);
			App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet3->collider, shot_box, 135, 1);
			App->particles->AddParticle(*shoot_start, position.x + 24, position.y + 30, shoot_start->collider, nullrect, 135);
			last_shot = SDL_GetTicks();
		}
	}
}
