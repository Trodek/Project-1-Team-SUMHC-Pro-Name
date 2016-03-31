#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneLevels::ModuleSceneLevels()
{
	// map
	map.x = 0;
	map.y = 15063;
	map.w = 256;
	map.h = 320;
}

ModuleSceneLevels::~ModuleSceneLevels()
{}

// Load assets
bool ModuleSceneLevels::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Map/Map.png");

	App->audio->Enable();
	App->player->Enable();

	return ret;
}

// Load assets
bool ModuleSceneLevels::CleanUp()
{
	LOG("Unloading Levels stage");
	App->player->Disable();
	App->audio->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneLevels::Update()
{
	// Map movement

	int speed = 5;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1){
		if (map.y > 0) map.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1){
		if (map.y < 15063) map.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->title, 1.0f);
	}
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &map, 3); // Map


	return UPDATE_CONTINUE;
}