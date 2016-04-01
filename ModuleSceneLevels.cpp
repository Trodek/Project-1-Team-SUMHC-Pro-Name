#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"


ModuleSceneLevels::ModuleSceneLevels()
{
	// map
	map.x = 0;
	map.y = 15063;
	map.w = 240;
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

	App->player->Enable();

	return ret;
}

// Load assets
bool ModuleSceneLevels::CleanUp()
{
	LOG("Unloading Levels stage");

	//Diable player
	App->player->Disable();
	
	//Stop audio and reset audio state
	App->audio->StopAudio();
	App->audio->ResetState();

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

	//Check song to play
	if (map.y > 11489) App->audio->PlayMusic(App->audio->level1, LOOP);
	else if (map.y < 11489 && map.y > 6436) App->audio->PlayMusic(App->audio->level2, LOOP);
	else App->audio->PlayMusic(App->audio->level3, LOOP);

	return UPDATE_CONTINUE;
}