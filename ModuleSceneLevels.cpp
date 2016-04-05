#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
ModuleSceneLevels::ModuleSceneLevels()
{
	// map
	map.x = 0;
	map.y = 0;
	map.w = 240;
	map.h = 15383;

	//set start point camera
	camera_y = -15063;
}

// MAP RESET FUNCTION
bool ModuleSceneLevels::CameraReset(){
	camera_y = -15063;
	return true;
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
		if (camera_y < 0) camera_y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1){
		if (camera_y > -15063) camera_y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->losescreen, 1.0f);
	}
	if (map.y <0){
		App->fade->FadeToBlack(this, (Module*)App->winscreen, 0.3f);
	}
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, camera_y, &map, 3); // Map

	//Check song to play
	if (camera_y < -11489) App->audio->PlayMusic(App->audio->level1, LOOP);
	else if (camera_y > -11489 && camera_y < -6436) App->audio->PlayMusic(App->audio->level2, LOOP);
	else App->audio->PlayMusic(App->audio->level3, LOOP);

	return UPDATE_CONTINUE;
}