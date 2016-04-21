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

	tex = App->particles->big_turret_bullet.tex;

	if (x > 120)
		tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Big Turret/big turret flip.png");

	collider = App->collisions->AddCollider({ 0, 0, 63, 64 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &idle;
	last_shot = SDL_GetTicks();
	hp = 60;
	points = 810;

	turret_bullet = &App->particles->big_turret_bullet;
	shoot_start = &App->particles->big_turret_bullet_start;

	dead = &App->particles->big_turret_dead;
	
}

void EnemyBigTurret::UpdateAnim()
{
}

void EnemyBigTurret::Shot(){

	

	now = SDL_GetTicks();

	if (hp>0){
		if (now - last_shot > 400){
			if (position.x < 120){
				App->particles->SetParticleSpeed(turret_bullet, 3.53f, 2.0f);
				App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet->collider, shot_box, 135);
				App->particles->SetParticleSpeed(turret_bullet, 3.53f, 3.5f);
				App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet->collider, shot_box, 135);
				App->particles->SetParticleSpeed(turret_bullet, 3.53f, 4.5f);
				App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet->collider, shot_box, 135);
				App->particles->AddParticle(*shoot_start, position.x + 24, position.y + 30, shoot_start->collider, nullrect, 135);
				last_shot = SDL_GetTicks();
			}
			else{
				App->particles->SetParticleSpeed(turret_bullet, -3.53f, 2.0f);
				App->particles->AddParticle(*turret_bullet, position.x + 16, position.y + 42, turret_bullet->collider, shot_box, 135);
				App->particles->SetParticleSpeed(turret_bullet, -3.53f, 3.5f);
				App->particles->AddParticle(*turret_bullet, position.x + 16, position.y + 42, turret_bullet->collider, shot_box, 135);
				App->particles->SetParticleSpeed(turret_bullet, -3.53f, 4.5f);
				App->particles->AddParticle(*turret_bullet, position.x + 16, position.y + 42, turret_bullet->collider, shot_box, 135);
				App->particles->AddParticle(*shoot_start, position.x+5, position.y + 35, shoot_start->collider, nullrect, 135);
				last_shot = SDL_GetTicks();
			}
		}
	}
}
