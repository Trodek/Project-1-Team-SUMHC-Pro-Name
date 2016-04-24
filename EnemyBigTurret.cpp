#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "EnemyBigTurret.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleEnemies.h"

#define nullrect {0,0,0,0} 
#define shot_box {0,0,14,14}

EnemyBigTurret::EnemyBigTurret(int x, int y,ENEMY_TYPES types) : Enemy(x, y,types)
{
	idle.PushBack({ 16, 24, 63, 64 });

	damaged.PushBack({ 6, 137, 16, 38 });
	damaged.PushBack({ 31, 137, 16, 38 });
	damaged.PushBack({ 53, 137, 16, 38 });
	damaged.PushBack({ 74, 137, 16, 38 });
	damaged.speed = 0.6f;

	damaged2.PushBack({ 6, 137, 16, 38 });
	damaged2.PushBack({ 31, 137, 16, 38 });
	damaged2.PushBack({ 53, 137, 16, 38 });
	damaged2.PushBack({ 74, 137, 16, 38 });
	damaged2.speed = 0.6f;

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
				if (count == 0)
					App->particles->SetParticleSpeed(turret_bullet, 3.53f, 2.0f);
				if (count == 1)
					App->particles->SetParticleSpeed(turret_bullet, 3.53f, 3.5f);
				if (count == 2)
					App->particles->SetParticleSpeed(turret_bullet, 3.53f, 4.5f);
				App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet->collider, shot_box, 135);
				App->particles->AddParticle(*shoot_start, position.x + 24, position.y + 30, shoot_start->collider, nullrect, 135);
				last_shot = SDL_GetTicks();
			}
			else{
				if (count == 0)
					App->particles->SetParticleSpeed(turret_bullet, -3.53f, 2.0f);
				if (count == 1)
					App->particles->SetParticleSpeed(turret_bullet, -3.53f, 3.5f);
				if (count == 2)
					App->particles->SetParticleSpeed(turret_bullet, -3.53f, 4.5f);
				App->particles->AddParticle(*turret_bullet, position.x + 16, position.y + 42, turret_bullet->collider, shot_box, 135);
				App->particles->AddParticle(*shoot_start, position.x + 5, position.y + 35, shoot_start->collider, nullrect, 135);
				last_shot = SDL_GetTicks();

			}
			if (count == 2){
				increase = false;
			}
			else if (count == 0){
				increase = true;
			}
			if (increase) count++;
			else count--;
		}
		if (hp < 35){
			if (position.x<120)
				App->render->Blit(tex, position.x + 35, position.y - 18, &(damaged.GetCurrentFrame()));
			else App->render->Blit(tex, position.x + 15, position.y - 18, &(damaged.GetCurrentFrame()));
			if (hp < 15){
				if (position.x<120)
					App->render->Blit(tex, position.x + 15, position.y , &(damaged2.GetCurrentFrame()));
				else  App->render->Blit(tex, position.x + 35, position.y, &(damaged2.GetCurrentFrame()));
			}

		}
	}
}
