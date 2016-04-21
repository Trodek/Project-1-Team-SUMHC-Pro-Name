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

	//run anim
	run.PushBack({ 13, 39, 80, 124 });
	run.PushBack({ 107, 39, 80, 123 });
	run.PushBack({ 206, 39, 80, 124 });
	run.PushBack({ 305, 39, 80, 125 });
	run.speed = 0.3f;
	run.loop = true;
}

ModuleTruck::~ModuleTruck()
{}

// Load assets
bool ModuleTruck::Start()
{
	LOG("Loading basic green enemy textures");
	truck_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Truck.png");
	bool ret = true;
	current_animation = &run;

	//truck_collider = App->collisions->AddCollider({ 0, 0, 70, 110 }, COLLIDER_ENEMY, this);

	return ret;
}

bool ModuleTruck::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;

	App->textures->Unload(truck_tex);

	return true;
}

// Update: draw background
update_status ModuleTruck::Update()
{

	now = SDL_GetTicks();

	if (!dead){
		App->render->Blit(truck_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	else{

	}

	//truck_collider->SetPos(position.x, position.y);

	return UPDATE_CONTINUE;
}

void ModuleTruck::OnCollision(Collider* c1, Collider* c2) {
	if (truck_collider == c1 && truck_collider != nullptr){
		if (c2->type == COLLIDER_PLAYER_SHOT){
			dead = true;
			
		}
	}
}