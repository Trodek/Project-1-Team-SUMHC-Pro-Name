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
	sublightanim.speed = 0.06f;
	//Lights

	lights.PushBack({ 0, 0, 256, 15383 });
	lights.PushBack({ 256, 0, 256, 15383 });
	lights.speed = 0.03f;
	// Lava
	lavaanim.PushBack({ 0, 0, 256, 15383 });
	lavaanim.PushBack({ 256, 0, 256, 15383 });
	lavaanim.PushBack({ 512, 0, 256, 15383 });
	lavaanim.speed = 0.03f;
	
	
}

// CAMERA RESET FUNCTION
bool ModuleSceneLevels::CameraReset(){
	camera_y = -15063*SCREEN_SIZE;
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

	//App->collisions->AddCollider({0,15070,240,5}, COLLIDER_WALL);
	//Level2 boss
	App->collisions->AddCollider({ 0, 6254, 92, 180 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 150, 6254, 92, 180 }, COLLIDER_WALL);
	//Level3 lava
	App->collisions->AddCollider({ 0, 5604, 42, 318 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 42, 5703, 27, 119 }, COLLIDER_HOLE);
	//Level3 lava
	App->collisions->AddCollider({ 0, 5203, 75, 156 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 75, 5271, 32, 88 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 53, 5359, 52, 94 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 107, 5325, 33, 96 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 140, 5356, 21, 63 }, COLLIDER_HOLE);
	//Levek3 lava
	App->collisions->AddCollider({ 181, 5176, 32, 58 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 212, 5144, 30, 149 }, COLLIDER_HOLE);
	//Level3 wall(lassers)
	App->collisions->AddCollider({ 0, 4705, 66, 93 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 190, 4705, 66, 93 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 4318, 16, 388 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 223, 4318, 16, 388 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 4225, 66, 93 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 193, 4225, 66, 93 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 29, 3874, 35, 62 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 64, 3874, 33, 93 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 97, 3874, 30, 126 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 127, 3908, 67, 59 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 0, 3746, 32, 97 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 32, 3746, 32, 62 }, COLLIDER_WALL);
	//Level 1













	App->render->camera.y = -15063*SCREEN_SIZE;

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
	App->render->Blit(lava, 0, 0, &lavaanim.GetCurrentFrame());
	App->render->Blit(sublighttex, 0, 0, &sublightanim.GetCurrentFrame());
	App->render->Blit(graphics, 0, 0, &map); // Map
	App->render->Blit(on_bg, 0, 0, &lights.GetCurrentFrame());



	
	//TEST
	
	

	//Check song to play
	if (App->render->camera.y < -11489) App->audio->PlayMusic(level1_song, LOOP);
	else if (App->render->camera.y > -11489 && App->render->camera.y < -6436) App->audio->PlayMusic(level2_song, LOOP);
	else App->audio->PlayMusic(level3_song, LOOP);

	return UPDATE_CONTINUE;
}