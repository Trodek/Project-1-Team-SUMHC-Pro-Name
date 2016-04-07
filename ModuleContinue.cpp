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

	graphics = App->textures->Load("Sprites/UI/ui_continue_small.png");
	continue_song = App->audio->LoadMusic("Sounds/Music/continue.ogg");
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

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &continue_screen, 0.75f); // background

	// swap Scene
	if (!(App->audio->IsPlaying())){
		App->fade->FadeToBlack(this, (Module*)App->namescreen, 1.0f);
	}

	return UPDATE_CONTINUE;
}