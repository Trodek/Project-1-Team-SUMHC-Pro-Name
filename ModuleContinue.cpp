#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleContinue.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleSceneLevels.h"
#include "SDL/include/SDL_timer.h"


ModuleContinue::ModuleContinue()
{
	// ground
	continue_screen.x = 0;
	continue_screen.y = 0;
	continue_screen.w = 240;
	continue_screen.h = 320;

}

ModuleContinue::~ModuleContinue()
{}

// Load assets
bool ModuleContinue::Start()
{
	LOG("Loading Title scene");

	born = SDL_GetTicks();

	continue_song = App->audio->LoadMusic("OutZone/Sounds/Music/continue.ogg");
	graphics = App->textures->Load("OutZone/Sprites/UI/ui_continue_small.png");
	App->audio->PlayMusic(continue_song, ONCE);

	return true;
}

// UnLoad assets
bool ModuleContinue::CleanUp()
{
	LOG("Unloading Title scene");
	
	App->textures->Unload(graphics);

	App->audio->StopAudio();
	App->audio->UnloadMusic(continue_song);

	return true;
}

// Update: draw background
update_status ModuleContinue::Update()
{
	now = SDL_GetTicks();
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &continue_screen, 0.75f); // background

	// swap Scene
	if (now-born>10000){
		App->fade->FadeToBlack(this, (Module*)App->namescreen, 1.0f);
	}

	return UPDATE_CONTINUE;
}