#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneTitle.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneTitle::ModuleSceneTitle()
{
	// ground
	title_screen.x = 0;
	title_screen.y = 0;
	title_screen.w = 256;
	title_screen.h = 320;

}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading Title scene");
	
	graphics = App->textures->Load("Sprites/UI/ui_maintitle.png");
	
	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading Title scene");
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneTitle::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &title_screen, 0.75f); // background
	

	// TODO 3: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
	}

	return UPDATE_CONTINUE;
}