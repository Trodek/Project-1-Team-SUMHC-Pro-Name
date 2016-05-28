#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBomb.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBomb.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"



ModuleBomb::ModuleBomb()
{
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 240, 0, 240, 320 });
	bombanim.PushBack({ 480, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 720, 0, 240, 320 });
	bombanim.PushBack({ 960, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 1200, 0, 240, 320 });
	bombanim.PushBack({ 1440, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 1680, 0, 240, 320 });
	bombanim.PushBack({ 1920, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 2160, 0, 240, 320 });
	bombanim.PushBack({ 2400, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 2640, 0, 240, 320 });
	bombanim.PushBack({ 2880, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 3120, 0, 240, 320 });
	bombanim.PushBack({ 3360, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.PushBack({ 3600, 0, 240, 320 });
	bombanim.PushBack({ 3840, 0, 240, 320 });
	bombanim.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bombanim.speed = 0.8f;
	bombanim.loop = false;

}

ModuleBomb::~ModuleBomb()
{}

// Load assets
bool ModuleBomb::Start()
{
	
	LOG("Loading Bomb");
	bool ret = true;
	bombtex = App->textures->Load("OutZone/Sprites/Weapon Shots/bomb.png");

	return true;
}

// UnLoad assets
bool ModuleBomb::CleanUp()
{
	LOG("Unloading Bomb");
	App->textures->Unload(bombtex);

	return true;
}

// Update: draw background
update_status ModuleBomb::Update()
{
	
	// Draw everything --------------------------------------
	if (pressed){
		
		if (!bombanim.Finished()){
			App->render->Blit(bombtex, 0, -App->render->camera.y / 3, &(bombanim.GetCurrentFrame()));
			if (!collider_create){
				BombCollider = App->collisions->AddCollider({ 0, (-App->render->camera.y) / 3, SCREEN_WIDTH, SCREEN_HEIGHT }, COLLIDER_BOMB, this);
				collider_create = true;
			}
		}
		else{
			pressed = false;
			bombanim.Reset();
			BombCollider->to_delete = true;
			collider_create = false;
		}
	}


	return UPDATE_CONTINUE;
}
