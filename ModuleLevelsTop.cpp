#include "ModuleLevelsTop.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Globals.h"
#include "Application.h"

ModuleLevelsTop::ModuleLevelsTop(){
	// level1
	level4.x = 0;
	level4.y = 0;
	level4.w = 240;
	level4.h = 7519;

}

ModuleLevelsTop::~ModuleLevelsTop(){}

bool ModuleLevelsTop::Start(){

	LOG("Loading Level Top-----");

	level4_top = App->textures->Load("OutZone/Sprites/Map/level4_top.png");

	return true;
}

bool ModuleLevelsTop::CleanUp(){

	App->textures->Unload(level4_top);

	return true;
}

update_status ModuleLevelsTop::Update(){
	
	App->render->Blit(level4_top, 0, 0, &level4);

	return UPDATE_CONTINUE;
}