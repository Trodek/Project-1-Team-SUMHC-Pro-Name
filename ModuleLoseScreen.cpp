#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleLoseScreen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleAudio.h"


ModuleLoseScreen::ModuleLoseScreen()
{
	// ground
	lose_screen.x = 0;
	lose_screen.y = 0;
	lose_screen.w = 256;
	lose_screen.h = 320;

}

ModuleLoseScreen::~ModuleLoseScreen()
{}

// Load assets
bool ModuleLoseScreen::Start()
{
	LOG("Loading Lose Screen");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Ui/ui_gameover2.png");

	App->player->Disable();

	// Play gameover audio
	App->audio->PlayMusic(App->audio->gameover, LOOP);

	return true;
}

// UnLoad assets
bool ModuleLoseScreen::CleanUp()
{
	LOG("Unloading Lose scene");

	// Stop Audio
	App->audio->StopAudio();

	return true;
}

// Update: draw background
update_status ModuleLoseScreen::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &lose_screen, 0.75f); // background


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->continuescreen,0.5f);
	}


	return UPDATE_CONTINUE;
}