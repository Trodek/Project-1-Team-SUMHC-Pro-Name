#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleContinue.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
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

	//Continue? Sprite
	cont.x = 1;
	cont.y = 191;
	cont.w = 119;
	cont.h = 25;

	//number Sprite

	x = 118;
	y = 155;
	number.w = 26;
	number.h = 35;

}

ModuleContinue::~ModuleContinue()
{}

// Load assets
bool ModuleContinue::Start()
{
	LOG("Loading Title scene");
	actual = 9;
	born = SDL_GetTicks();
	time_elapsed = SDL_GetTicks();

	continue_song = App->audio->LoadMusic("OutZone/Sounds/Music/continue.ogg");
	background = App->textures->Load("OutZone/Sprites/Title/BluePlayer.png");

	App->audio->PlayMusic(continue_song, ONCE);

	App->ui->cont = true;

	return true;
}

// UnLoad assets
bool ModuleContinue::CleanUp()
{
	LOG("Unloading NameScreen scene");
	
	App->textures->Unload(background);

	App->ui->cont = false;

	App->audio->StopAudio();
	App->audio->UnloadMusic(continue_song);

	return true;
}

// Update: draw background
update_status ModuleContinue::Update()
{
	now = SDL_GetTicks();
	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, &continue_screen, 0.75f); // background
	App->render->Blit(App->ui->ui_graphics, 1, 152, &cont);
	number.x = x;
	number.y = y;
	App->render->Blit(App->ui->ui_graphics, 47, 189, &number);
	if (now - time_elapsed > 1000) {
		actual--;
		time_elapsed = SDL_GetTicks();
		if (actual == 4) {
			y = 116;
			x = 118;
		}
		else {
			x -= 29; 
		}
	}

	// swap Scene
	if (now - born > 9000)
		if (App->ui->TopScore())
			App->fade->FadeToBlack(this, (Module*)App->title, 1.0f);
		else
			App->fade->FadeToBlack(this, (Module*)App->scorescreen, 1.0f);
	if (now - born > 9499) {
		actual = 9;
		y = 155;
		x = 118;
	}

	return UPDATE_CONTINUE;
}