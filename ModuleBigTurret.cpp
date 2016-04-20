#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleBigTurret.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneLevels.h"
#include "SDL/include/SDL_timer.h"

#define nullrect {0,0,0,0} 
#define laserbox_p0 {0,0,14,14}

ModuleBigTurret::ModuleBigTurret()
{
	position.x = 0;
	position.y = 13704;

	//Turret idle anim
	idle.PushBack({ 16, 24, 63, 64 });

	//Turret dead fire anim
	dead_fire.PushBack({ 0, 0, 64, 65 });
	dead_fire.PushBack({ 64, 0, 64, 65 });
	dead_fire.PushBack({ 128, 0, 64, 65 });
	dead_fire.PushBack({ 192, 0, 64, 65 });
	dead_fire.PushBack({ 256, 0, 64, 65 });
	dead_fire.speed = 0.2f;
	dead_fire.loop = true;

}

ModuleBigTurret::~ModuleBigTurret()
{}

// Load assets
bool ModuleBigTurret::Start()
{
	LOG("Loading basic green enemy textures");
	big_turret_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Big Turret/big turret.png");
	big_turret_fire_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Big Turret/big turret fire.png");
	bool ret = true;
	current_animation = &idle;
	turret_bullet = &App->particles->big_turret_bullet;
	turret_bullet2 = &App->particles->big_turret_bullet;
	turret_bullet3 = &App->particles->big_turret_bullet;
	shoot_start = &App->particles->big_turret_bullet_start;

	big_turret_collider = App->collisions->AddCollider({ 0, 0, 63, 64 }, COLLIDER_ENEMY, this);
	big_turret_collider->SetPos(position.x, position.y);

	last_shot = SDL_GetTicks();

	return ret;
}

bool ModuleBigTurret::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;

	App->textures->Unload(big_turret_tex);
	App->textures->Unload(big_turret_fire_tex);

	return true;
}

// Update: draw background
update_status ModuleBigTurret::Update()
{
	
	now = SDL_GetTicks();

	if (!dead){
		App->render->Blit(big_turret_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
		if (now - last_shot > 400 && start_shooting){
			App->particles->SetParticleSpeed(turret_bullet, 3.53f, 2.0f);
			App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet->collider, laserbox_p0, 135);
			App->particles->SetParticleSpeed(turret_bullet, 3.53f, 3.5f);
			App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet2->collider, laserbox_p0, 135,0.9);
			App->particles->SetParticleSpeed(turret_bullet, 3.53f, 4.5f);
			App->particles->AddParticle(*turret_bullet, position.x + 35, position.y + 37, turret_bullet3->collider, laserbox_p0, 135,1);
			App->particles->AddParticle(*shoot_start, position.x + 24, position.y + 30, shoot_start->collider, nullrect, 135);
			last_shot = SDL_GetTicks();
		}
	}
	else{
		App->render->Blit(big_turret_fire_tex, position.x, position.y+5, &(current_animation->GetCurrentFrame()));
	}


	return UPDATE_CONTINUE;
}

void ModuleBigTurret::OnCollision(Collider* c1, Collider* c2) {
	if (big_turret_collider == c1 && big_turret_collider != nullptr){
		if (c2->type == COLLIDER_PLAYER_SHOT){
			dead = true;
			current_animation = &dead_fire;
		} 
	}
}