#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleInput.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// Map
	map.x = 0;
	map.y = 15063;
	map.w = 256;
	map.h = 320;

}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Map/Map.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Map movement

	int speed = 5;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1){
		if (map.y > 0) map.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1){
		if (map.y < 15063) map.y += speed;
	}
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &map, 3); // Map
	

	return UPDATE_CONTINUE;
}