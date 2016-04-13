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
#include "SDL/include/SDL_timer.h"

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

	born = SDL_GetTicks();

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
	now = SDL_GetTicks();

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &win_screen, 0.75f); // background

	if (now-born>5000){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
	}

	return UPDATE_CONTINUE;
}