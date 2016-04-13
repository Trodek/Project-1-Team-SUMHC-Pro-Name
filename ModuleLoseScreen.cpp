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
#include "SDL/include/SDL_timer.h"



ModuleLoseScreen::ModuleLoseScreen()
{
	// ground
	lose_screen.x = 0;
	lose_screen.y = 0;
	lose_screen.w = 240;
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
	born = SDL_GetTicks();
	// Load and Play gameover audio
	gameover_song = App->audio->LoadMusic("Sounds/Music/gameover.ogg");
	App->audio->PlayMusic(gameover_song, ONCE);

	return true;
}

// UnLoad assets
bool ModuleLoseScreen::CleanUp()
{
	LOG("Unloading Lose scene");

	App->textures->Unload(graphics);

	// Stop Audio
	App->audio->StopAudio();
	App->audio->UnloadMusic(gameover_song);

	return true;
}

// Update: draw background
update_status ModuleLoseScreen::Update()
{

	// Draw everything --------------------------------------
	now = SDL_GetTicks();

	App->render->Blit(graphics, 0, 0, &lose_screen, 0.75f); // background

	if (now-born>5000){
		App->fade->FadeToBlack(this, (Module*)App->continuescreen,0.5f);
	}


	return UPDATE_CONTINUE;
}