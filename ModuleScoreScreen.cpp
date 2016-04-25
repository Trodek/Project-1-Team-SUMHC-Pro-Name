#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleScoreScreen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScoreScreen.h"




ModuleScoreScreen::ModuleScoreScreen()
{
	// ground
	score_screen.x = 0;
	score_screen.y = 0;
	score_screen.w = 240;
	score_screen.h = 320;


}

ModuleScoreScreen::~ModuleScoreScreen()
{}

// Load assets
bool ModuleScoreScreen::Start()
{
	LOG("Loading score Screen");
	bool ret = true;
	graphics = App->textures->Load("OutZone/Sprites/Scores/Ranking.png");


	return true;
}

// UnLoad assets
bool ModuleScoreScreen::CleanUp()
{
	LOG("Unloading score scene");
	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModuleScoreScreen::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &score_screen, 0.75f); // background
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->title, 0.5f);
	}




	return UPDATE_CONTINUE;
}




