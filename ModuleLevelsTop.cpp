#include "ModuleLevelsTop.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Globals.h"
#include "Application.h"

ModuleLevelsTop::ModuleLevelsTop(){
	// level1
	level1.x = 0;
	level1.y = 0;
	level1.w = 240;
	level1.h = 3927;

	//level2
	level2.x = 0;
	level2.y = 0;
	level2.w = 240;
	level2.h = 5441;

	//level3
	level3.x = 0;
	level3.y = 0;
	level3.w = 240;
	level3.h = 6855;
}

ModuleLevelsTop::~ModuleLevelsTop(){}

bool ModuleLevelsTop::Start(){

	level1_top = App->textures->Load("Sprites/Map/level1_top.png");
	level2_top = App->textures->Load("Sprites/Map/level2_top.png");
	level3_top = App->textures->Load("Sprites/Map/level3_top.png");

	return true;
}

bool ModuleLevelsTop::CleanUp(){

	App->textures->Unload(level1_top);
	App->textures->Unload(level2_top);
	App->textures->Unload(level3_top);

	return true;
}

update_status ModuleLevelsTop::Update(){
	
	App->render->Blit(level1_top, 0, 11456, &level1);
	App->render->Blit(level2_top, 0, 6435, &level2);
	App->render->Blit(level3_top, 0, 0, &level3);

	return UPDATE_CONTINUE;
}