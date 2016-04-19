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
#define laserbox_p0 {0,0,4,4}

ModuleBigTurret::ModuleBigTurret()
{
	position.x = 0;
	position.y = 13704;

	//Turret idle anim
	idle.PushBack({ 16, 24, 63, 64 });

}

ModuleBigTurret::~ModuleBigTurret()
{}

// Load assets
bool ModuleBigTurret::Start()
{
	LOG("Loading basic green enemy textures");
	big_turret_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/big turret.png");
	bool ret = true;
	current_animation = &idle;
	turret_bullet = &App->particles->big_turret_bullet;
	shoot_start = &App->particles->big_turret_bullet_start;
	//laser_p0 = &App->particles->basic_laser_p0;

	big_turret_collider = App->collisions->AddCollider({ 0, 0, 63, 64 }, COLLIDER_ENEMY, this);
	big_turret_collider->SetPos(position.x, position.y);

	return ret;
}

bool ModuleBigTurret::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;

	App->textures->Unload(big_turret_tex);

	return true;
}

// Update: draw background
update_status ModuleBigTurret::Update()
{
	
	now = SDL_GetTicks();

	if (!dead){
		App->render->Blit(big_turret_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));

		App->particles->SetParticleSpeed(shoot_start, 3.53f, 3.53f);
		App->particles->SetColliderCorrection(shoot_start, 4, 10);
		App->particles->AddParticle(*turret_bullet, position.x + 20, position.y + 17, turret_bullet->collider, laserbox_p0, 135);
		App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 19, shoot_start->collider, nullrect, 135);
	}
	else{
		
	}


	return UPDATE_CONTINUE;
}

void ModuleBigTurret::OnCollision(Collider* c1, Collider* c2) {
	if (big_turret_collider == c1 && big_turret_collider != nullptr){
		if (c2->type == COLLIDER_PLAYER_SHOT){
			dead = true;
		} 
	}
}