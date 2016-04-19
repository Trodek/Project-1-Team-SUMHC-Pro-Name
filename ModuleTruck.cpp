#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTruck.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneLevels.h"
#include "SDL/include/SDL_timer.h"

#define nullrect {0,0,0,0} 
#define laserbox_p0 {0,0,4,4}

ModuleTruck::ModuleTruck()
{
	position.x = 120;
	position.y = 14000;

	//Turret idle anim
	idle.PushBack({ 16, 24, 63, 64 });

	//Shoot Bullet anim
	bullet.PushBack({ 4, 98, 30, 31 });
	bullet.PushBack({ 43, 107, 14, 14 });
	bullet.PushBack({ 66, 106, 14, 14 });

}

ModuleTruck::~ModuleTruck()
{}

// Load assets
bool ModuleTruck::Start()
{
	LOG("Loading basic green enemy textures");
	big_turret_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/big turret.png");
	bool ret = true;
	current_animation = &idle;
	laser_p0 = &App->particles->basic_laser_p0;
	shoot_start = &App->particles->shoot_start;

	big_turret_collider = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, this);

	return ret;
}

bool ModuleTruck::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;

	App->textures->Unload(big_turret_tex);

	return true;
}

// Update: draw background
update_status ModuleTruck::Update()
{

	now = SDL_GetTicks();

	if (!dead){
		App->render->Blit(big_turret_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	else{

	}


	return UPDATE_CONTINUE;
}

void ModuleTruck::OnCollision(Collider* c1, Collider* c2) {
	if (big_turret_collider == c1 && big_turret_collider != nullptr){
		if (c2->type == COLLIDER_PLAYER_SHOT){
			dead = true;
		}
	}
}