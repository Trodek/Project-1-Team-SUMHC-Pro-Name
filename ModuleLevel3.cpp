#include "Globals.h"
#include "Application.h"
#include "ModuleLevel2.h"
#include "ModuleLevel3.h"
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

ModuleLevel3::ModuleLevel3(){
	map.x = 0;
	map.y = 0;
	map.w = 240;
	map.h = 6855;
}

ModuleLevel3::~ModuleLevel3(){}

bool ModuleLevel3::Start(){
	LOG("Loading Level3 assets");
	bool ret = true;

	App->current_level = this;

	//Load map
	graphics = App->textures->Load("Sprites/Map/Level3.png");

	//Load song
	level3_song = App->audio->LoadMusic("Sounds/Music/level3.ogg");

	//Colliders
	//Level3 lava
	colliders.PushBack(App->collisions->AddCollider({ 0, 5604, 42, 318 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 42, 5703, 27, 119 }, COLLIDER_HOLE));
	//Level3 lava
	colliders.PushBack(App->collisions->AddCollider({ 0, 5203, 75, 156 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 75, 5271, 32, 88 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 53, 5359, 52, 94 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 107, 5325, 33, 96 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 140, 5356, 21, 63 }, COLLIDER_HOLE));
	//Levek3 lava
	colliders.PushBack(App->collisions->AddCollider({ 181, 5176, 32, 58 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 212, 5144, 30, 149 }, COLLIDER_HOLE));
	//Level3 wall(lassers)
	colliders.PushBack(App->collisions->AddCollider({ 0, 4705, 66, 93 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 190, 4705, 66, 93 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 0, 4318, 16, 388 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 223, 4318, 16, 388 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 0, 4225, 66, 93 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 193, 4225, 66, 93 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 29, 3874, 35, 62 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 64, 3874, 33, 93 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 97, 3874, 30, 126 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 127, 3908, 67, 59 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 3746, 32, 97 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 32, 3746, 32, 62 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 129, 3746, 32, 95 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 162, 3746, 32, 59 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 189, 3714, 32, 126 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 222, 3714, 32, 158 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 3650, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 64, 3585, 32, 62 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 96, 3585, 32, 127 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 127, 3555, 32, 93 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 190, 3586, 32, 62 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 222, 3586, 32, 94 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 3427, 32, 157 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 32, 3457, 32, 95 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 64, 3489, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 160, 3458, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 192, 3458, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 224, 3425, 32, 128 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 64, 3361, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 96, 3361, 32, 96 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 128, 3361, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 191, 3329, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 223, 3329, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 2576, 32, 145 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 32, 2609, 32, 77 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 128, 2609, 32, 77 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 160, 2593, 32, 127 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 192, 2593, 32, 127 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 224, 2609, 32, 77 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 63, 2481, 32, 80 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 66, 2372, 87, 59 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 104, 2431, 47, 129 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 65, 2482, 127, 79 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 98, 2450, 61, 32 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 159, 2481, 32, 80 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 2433, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 223, 2466, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 192, 2351, 32, 81 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 224, 2351, 32, 81 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 2271, 32, 96 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 32, 2271, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 127, 2273, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 190, 2241, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 222, 2241, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 63, 2081, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 95, 2081, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 190, 2081, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 222, 2050, 32, 96 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 2017, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 96, 1921, 32, 129 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 128, 1921, 32, 129 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 160, 1969, 32, 80 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 1890, 32, 96 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 32, 1921, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 224, 1921, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 96, 1825, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 160, 1809, 32, 81 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 192, 1809, 32, 81 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 224, 1809, 32, 81 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 1728, 32, 98 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 32, 1713, 32, 146 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 64, 1713, 32, 81 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 96, 1713, 32, 81 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 192, 1697, 32, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 224, 1697, 32, 64 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 1345, 63, 62 }, COLLIDER_WALL));
	//Level3 walls
	colliders.PushBack(App->collisions->AddCollider({ 175, 1345, 63, 62 }, COLLIDER_WALL));
	//Level3 hole
	colliders.PushBack(App->collisions->AddCollider({ 0, 1187, 64, 125 }, COLLIDER_HOLE));
	//Level3 hole
	colliders.PushBack(App->collisions->AddCollider({ 112, 1058, 65, 62 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 177, 1058, 30, 254 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 207, 993, 50, 319 }, COLLIDER_HOLE));
	//Level3 hole
	colliders.PushBack(App->collisions->AddCollider({ 0, 640, 32, 480 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 32, 707, 32, 286 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 64, 707, 32, 61 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 64, 864, 32, 128 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 96, 928, 32, 64 }, COLLIDER_HOLE));
	//Level3 hole
	colliders.PushBack(App->collisions->AddCollider({ 143, 708, 32, 60 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 175, 708, 32, 187 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 207, 642, 32, 284 }, COLLIDER_HOLE));
	//Level3 boss left
	colliders.PushBack(App->collisions->AddCollider({ 0, 365, 15, 147 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 15, 380, 15, 132 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 30, 395, 15, 117 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 45, 410, 15, 102 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 60, 425, 15, 87 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 75, 440, 15, 72 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 90, 455, 15, 57 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 105, 470, 15, 42 }, COLLIDER_HOLE_BOSS_LEFT));
	colliders.PushBack(App->collisions->AddCollider({ 120, 485, 7, 27 }, COLLIDER_HOLE_BOSS_LEFT));
	//Level3 boss right
	colliders.PushBack(App->collisions->AddCollider({ 127, 480, 30, 32 }, COLLIDER_HOLE_BOSS_RIGHT));
	colliders.PushBack(App->collisions->AddCollider({ 157, 467, 30, 45 }, COLLIDER_HOLE_BOSS_RIGHT));
	colliders.PushBack(App->collisions->AddCollider({ 187, 452, 30, 60 }, COLLIDER_HOLE_BOSS_RIGHT));
	colliders.PushBack(App->collisions->AddCollider({ 217, 440, 30, 72 }, COLLIDER_HOLE_BOSS_RIGHT));

	return true;
}

bool ModuleLevel3::CleanUp(){

	App->textures->Unload(graphics);

	App->audio->UnloadMusic(level3_song);

	for (int i = 0; i < colliders.size(); i++){
		App->collisions->EraseCollider(colliders[i]);
	}

	App->render->camera.y = 0;

	return true;
}

update_status ModuleLevel3::Update(){

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->losescreen, 1.0f);
		App->level2->Disable();
		App->render->camera.y = 0;
	}

	if (App->render->camera.y >= 0){
		App->fade->FadeToBlack(this, (Module*)App->winscreen, 1.0f);
	}

	if (App->render->camera.y > -6436) App->level2->Disable();

	if (App->render->camera.y > -6435){
		App->audio->PlayMusic(level3_song, LOOP);
		App->audio->UnloadMusic(App->level2->level2_song);
	}

	App->render->Blit(graphics, 0, 0, &map); // Map

	return UPDATE_CONTINUE;
}