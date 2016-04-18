#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
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

ModuleLevel1::ModuleLevel1()
{
	map.x = 0;
	map.y = 0;
	map.w = 240;
	map.h = 3927;
}

ModuleLevel1::~ModuleLevel1() {}

bool ModuleLevel1::Start(){

	LOG("Loading Level1 assets");
	bool ret = true;

	App->current_level = this;

	//Load map
	graphics = App->textures->Load("Sprites/Map/Level1.png");

	//Load song
	level1_song = App->audio->LoadMusic("Sounds/Music/level1.ogg");

	//Enable Player and Collisions
	App->player->Enable();
	App->collisions->Enable();

	//Collisions
	//start
	colliders.PushBack(App->collisions->AddCollider({ 0, 14893, 98, 212 }, COLLIDER_WALL));//LEFT
	colliders.PushBack(App->collisions->AddCollider({ 0, 14873, 75, 20 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 160, 14907, 96, 87 }, COLLIDER_WALL));//RIGHT
	colliders.PushBack(App->collisions->AddCollider({ 178, 14993, 78, 30 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 195, 15023, 61, 17 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 226, 15040, 30, 19 }, COLLIDER_WALL));
	//rocks

	colliders.PushBack(App->collisions->AddCollider({ 129, 14357, 31, 38 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 192, 14293, 31, 38 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 1, 14164, 30, 38 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 162, 14001, 31, 38 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 66, 13328, 29, 38 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 193, 13297, 31, 38 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 0, 13265, 32, 38 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 95, 13171, 33, 38 }, COLLIDER_WALL));
	// walls
	colliders.PushBack(App->collisions->AddCollider({ 0, 13700, 123, 145 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 0, 13843, 32, 35 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 198, 13699, 58, 143 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 0, 13414, 61, 141 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 136, 13410, 120, 146 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 0, 11925, 95, 82 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 163, 11925, 93, 79 }, COLLIDER_WALL));

	App->render->camera.y = -15063 * SCREEN_SIZE;

	return ret;
}

bool ModuleLevel1::CleanUp(){

	App->textures->Unload(graphics);

	for (int i = 0; i < colliders.size(); i++){
		App->collisions->EraseCollider(colliders[i]);
	}

	return true;
}

update_status ModuleLevel1::Update(){

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->losescreen, 1.0f);
		App->render->camera.y = 0;
	}

	//load level2
	if (App->render->camera.y > -117876) App->level2->Enable();

	App->audio->PlayMusic(level1_song, LOOP);
	App->render->Blit(graphics, 0, 11456, &map); // Map

	return UPDATE_CONTINUE;
}