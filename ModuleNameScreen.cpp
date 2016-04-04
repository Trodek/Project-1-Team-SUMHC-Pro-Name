#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleNameScreen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleNameScreen.h"
#include "ModuleScoreScreen.h"


ModuleNameScreen::ModuleNameScreen()
{
	// ground
	name_screen.x = 0;
	name_screen.y = 0;
	name_screen.w = 240;
	name_screen.h = 320;

}

ModuleNameScreen::~ModuleNameScreen()
{}

// Load assets
bool ModuleNameScreen::Start()
{
	LOG("Loading name Screen");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Ui/ui_savescore2.png");


	return true;
}

// UnLoad assets
bool ModuleNameScreen::CleanUp()
{
	LOG("Unloading name scene");

	return true;
}

// Update: draw background
update_status ModuleNameScreen::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &name_screen, 0.75f); // background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->scorescreen);
	}



	return UPDATE_CONTINUE;
}