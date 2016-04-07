#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleWinScreen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleSceneLevels.h"

ModuleWinScreen::ModuleWinScreen()
{
	// ground
	win_screen.x = 0;
	win_screen.y = 0;
	win_screen.w = 240;
	win_screen.h = 320;

}

ModuleWinScreen::~ModuleWinScreen()
{}

// Load assets
bool ModuleWinScreen::Start()
{
	LOG("Loading Win Screen");
	bool ret = true;
	graphics = App->textures->Load("Sprites/UI/ui_endgame2.png");



	return true;
}

// UnLoad assets
bool ModuleWinScreen::CleanUp()
{
	LOG("Unloading Win scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleWinScreen::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &win_screen, 0.75f); // background


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
	}
	

	return UPDATE_CONTINUE;
}