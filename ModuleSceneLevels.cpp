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
	//Level3 walls
	App->collisions->AddCollider({ 129, 3746, 32, 95 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 162, 3746, 32, 59 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 189, 3714, 32, 126 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 222, 3714, 32, 158 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 0, 3650, 32, 64 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 64, 3585, 32, 62 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 96, 3585, 32, 127 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 127, 3555, 32, 93 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 190, 3586, 32, 62 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 222, 3586, 32, 94 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 0, 3427, 32, 157 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 32, 3457, 32, 95 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 64, 3489, 32, 64 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 160, 3458, 32, 64 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 192, 3458, 32, 64 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 224, 3425, 32, 128 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 64, 3361, 32, 64 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 96, 3361, 32, 96 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 128, 3361, 32, 64 }, COLLIDER_WALL);
	//Level3 walls
	App->collisions->AddCollider({ 191, 3329, 32, 64 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 223, 3329, 32, 64 }, COLLIDER_WALL);


	//Level 1 start
	App->collisions->AddCollider({ 0, 14893, 98, 212 }, COLLIDER_WALL);//LEFT
	App->collisions->AddCollider({ 0, 14873, 75, 20 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 160, 14907, 96, 87 }, COLLIDER_WALL);//RIGHT
	App->collisions->AddCollider({ 178, 14993, 78, 30 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 195, 15023, 61, 17 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 226, 15040, 30, 19 }, COLLIDER_WALL);
	//level 1 rocks

	App->collisions->AddCollider({ 129, 14357, 31, 38 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 192, 14293, 31, 38 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 1, 14164, 30, 38 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 162, 14001, 31, 38 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 66, 13328, 29, 38 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 193, 13297, 31, 38 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 13265, 32, 38 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 95, 13171, 33, 38 }, COLLIDER_WALL);
	//Level 1 more walls
	App->collisions->AddCollider({ 0, 13700, 123, 145 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 13843, 32, 35 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 198, 13699, 58, 143 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 13414, 61, 141 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 136, 13410, 120, 146 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 11925, 95, 82 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 163, 11925, 93, 79 }, COLLIDER_WALL);
	//level 2 walls
	App->collisions->AddCollider({ 163, 11040, 93, 97 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 10550, 94, 73 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 161, 10552, 95, 73 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 9283, 97, 64 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 161, 9284, 95, 63 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 9154, 33, 64 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 97, 9178, 159, 41 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 87, 9007, 84, 171 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 64, 8641, 34, 132 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 161, 8641, 31, 131 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 8458, 75, 126 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 182, 8465, 74, 118 }, COLLIDER_WALL);
	//level 2 holes
	App->collisions->AddCollider({ 0, 10086, 68, 200 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 10285, 48, 22 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 189, 10090, 66, 196 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 207, 10286, 49, 19 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 73, 9959, 94, 58 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 171, 9799, 28, 90 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 197, 9831, 59, 56 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 44, 9767, 58, 121 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 9830, 44, 58 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 108, 9639, 132, 56 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 168, 9695, 67, 33 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 9640, 37, 57 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 9447, 38, 121 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 106, 9448, 29, 121 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 202, 9447, 55, 121 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 202, 7557, 54, 59 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 74, 7528, 59, 88 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 7527, 36, 89 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 202, 7398, 54, 90 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 75, 7364, 61, 93 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 138, 7396, 30, 93 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 7205, 42, 91 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 43, 7176, 27, 153 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 71, 7237, 34, 60 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 107, 7207, 26, 89 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 174, 7078, 82, 155 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 135, 7110, 39, 58 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 108, 7078, 27, 90 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 7079, 70, 57 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 6917, 69, 59 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 46, 6953, 87, 55 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 107, 6888, 27, 120 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 172, 6855, 84, 58 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 170, 6760, 28, 58 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 0, 6758, 68, 59 }, COLLIDER_HOLE);













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