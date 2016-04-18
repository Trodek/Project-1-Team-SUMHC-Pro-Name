#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
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

ModuleLevel2::ModuleLevel2(){
	map.x = 0;
	map.y = 0;
	map.w = 240;
	map.h = 5441;
}

ModuleLevel2::~ModuleLevel2(){

}

bool ModuleLevel2::Start(){
	LOG("Loading Level2 assets");
	bool ret = true;

	//Load map
	graphics = App->textures->Load("Sprites/Map/Level2.png");

	//Load song
	level2_song = App->audio->LoadMusic("Sounds/Music/level2.ogg");

	//Colliders
	//boss
	colliders.PushBack(App->collisions->AddCollider({ 0, 6254, 92, 180 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 150, 6254, 92, 180 }, COLLIDER_WALL));
	//walls
	colliders.PushBack(App->collisions->AddCollider({ 163, 11040, 93, 97 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 0, 10550, 94, 73 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 161, 10552, 95, 73 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 0, 9283, 97, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 161, 9284, 95, 63 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 0, 9154, 33, 64 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 97, 9178, 159, 41 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 87, 9007, 84, 171 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 64, 8641, 34, 132 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 161, 8641, 31, 131 }, COLLIDER_WALL));

	colliders.PushBack(App->collisions->AddCollider({ 0, 8458, 75, 126 }, COLLIDER_WALL));
	colliders.PushBack(App->collisions->AddCollider({ 182, 8465, 74, 118 }, COLLIDER_WALL));
	//holes
	colliders.PushBack(App->collisions->AddCollider({ 0, 10086, 68, 200 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 10285, 48, 22 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 189, 10090, 66, 196 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 207, 10286, 49, 19 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 73, 9959, 94, 58 }, COLLIDER_HOLE));

	colliders.PushBack(App->collisions->AddCollider({ 171, 9799, 28, 90 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 197, 9831, 59, 56 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 44, 9767, 58, 121 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 9830, 44, 58 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 108, 9639, 132, 56 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 168, 9695, 67, 33 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 9640, 37, 57 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 9447, 38, 121 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 106, 9448, 29, 121 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 202, 9447, 55, 121 }, COLLIDER_HOLE));

	colliders.PushBack(App->collisions->AddCollider({ 202, 7557, 54, 59 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 74, 7528, 59, 88 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 7527, 36, 89 }, COLLIDER_HOLE));

	colliders.PushBack(App->collisions->AddCollider({ 202, 7398, 54, 90 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 75, 7364, 61, 93 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 138, 7396, 30, 93 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 7205, 42, 91 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 43, 7176, 27, 153 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 71, 7237, 34, 60 }, COLLIDER_HOLE));

	colliders.PushBack(App->collisions->AddCollider({ 107, 7207, 26, 89 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 174, 7078, 82, 155 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 135, 7110, 39, 58 }, COLLIDER_HOLE));

	colliders.PushBack(App->collisions->AddCollider({ 108, 7078, 27, 90 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 7079, 70, 57 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 6917, 69, 59 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 46, 6953, 87, 55 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 107, 6888, 27, 120 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 172, 6855, 84, 58 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 170, 6760, 28, 58 }, COLLIDER_HOLE));
	colliders.PushBack(App->collisions->AddCollider({ 0, 6758, 68, 59 }, COLLIDER_HOLE));

	return ret;
}

bool ModuleLevel2::CleanUp(){

	App->textures->Unload(graphics);

	for (int i = 0; i < colliders.size(); i++){
		App->collisions->EraseCollider(colliders[i]);
	}

	return true;
}

update_status ModuleLevel2::Update(){

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->losescreen, 1.0f);
	}

	if (App->render->camera.y > -11455) App->level1->Disable();

	if (App->render->camera.y > -11456){
		App->audio->PlayMusic(level2_song, LOOP);
		App->audio->UnloadMusic(App->level1->level1_song);
	}
	App->render->Blit(graphics, 0, 6435, &map); // Map

	return UPDATE_CONTINUE;
}