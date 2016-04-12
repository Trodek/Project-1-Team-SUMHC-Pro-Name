#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
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
	//Sub-Lights
	sublightanim.PushBack({ 0, 0, 256, 15383 });
	sublightanim.PushBack({ 256, 0, 256, 15383 });
	sublightanim.speed = 0.06;
	//Lights

	lights.PushBack({ 0, 0, 256, 15383 });
	lights.PushBack({ 256, 0, 256, 15383 });
	lights.speed = 0.03f;
	// Lava
	lavaanim.PushBack({ 0, 0, 256, 15383 });
	lavaanim.PushBack({ 256, 0, 256, 15383 });
	lavaanim.PushBack({ 512, 0, 256, 15383 });
	lavaanim.speed = 0.03;
	
	
}

// CAMERA RESET FUNCTION
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
	on_bg = App->textures->Load("Sprites/Map/MAP LAYER ON.png");
	lava = App->textures->Load("Sprites/Map/lava.png");
	sublighttex = App->textures->Load("Sprites/Map/sublights.png");
	graphics = App->textures->Load("Sprites/Map/Map.png");
	
	level1_song = App->audio->LoadMusic("Sounds/Music/level1.ogg");
	level2_song = App->audio->LoadMusic("Sounds/Music/level2.ogg");
	level3_song = App->audio->LoadMusic("Sounds/Music/level3.ogg");

	//Enable Player and Collisions
	App->player->Enable();
	App->collisions->Enable();

	//App->collisions->AddCollider({0,15170,240,5}, COLLIDER_WALL);
	App->render->camera.y = -15063;

	CameraReset();

	return ret;
}

// Load assets
bool ModuleSceneLevels::CleanUp()
{
	LOG("Unloading Levels stage");

	// Unload textures
	App->textures->Unload(graphics);
	App->textures->Unload(on_bg);
	App->textures->Unload(lava);
	App->textures->Unload(sublighttex);

	//Disable player
	App->player->Disable();

	//Disable Collisions
	App->collisions->Disable();
	
	//Stop audio
	App->audio->StopAudio();
	App->audio->UnloadMusic(level1_song);
	App->audio->UnloadMusic(level2_song);
	App->audio->UnloadMusic(level3_song);

	App->render->camera.y = 0;

	return true;
}

// Update: draw background
update_status ModuleSceneLevels::Update()
{
	// Map movement

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->losescreen, 1.0f);
	}
	if (camera_y > 0){
		App->fade->FadeToBlack(this, (Module*)App->winscreen, 0.3f);
	}
	// Draw everything --------------------------------------
	App->render->Blit(lava, 0, 0, &lavaanim.GetCurrentFrame(),3);
	App->render->Blit(sublighttex, 0, 0, &sublightanim.GetCurrentFrame(),3);
	App->render->Blit(graphics, 0, 0, &map,3); // Map
	App->render->Blit(on_bg, 0, 0, &lights.GetCurrentFrame(),3);



	
	//TEST
	
	

	//Check song to play
	if (camera_y < -11489) App->audio->PlayMusic(level1_song, LOOP);
	else if (camera_y > -11489 && camera_y < -6436) App->audio->PlayMusic(level2_song, LOOP);
	else App->audio->PlayMusic(level3_song, LOOP);

	return UPDATE_CONTINUE;
}