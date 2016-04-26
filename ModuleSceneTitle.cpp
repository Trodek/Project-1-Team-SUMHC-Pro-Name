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
#include "ModuleSceneLevels.h"
#include "Path.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleUI.h"


ModuleSceneTitle::ModuleSceneTitle()
{
	// ground
	title_screen.x = 0;
	title_screen.y = 0;
	title_screen.w = 240;
	title_screen.h = 320;
	//
	title_anim.PushBack({ 0, 0,   200, 54 });
	title_anim.PushBack({ 0, 65,  200, 54 });
	title_anim.PushBack({ 0, 123, 200, 54 });
	title_anim.PushBack({ 0, 188, 200, 54 });
	title_anim.PushBack({ 0, 448, 200, 54 });
	title_anim.PushBack({ 0, 383, 200, 54 });
	title_anim.PushBack({ 0, 318, 200, 54 });
	title_anim.PushBack({ 0, 253, 200, 54 });


	title_anim.speed = 0.08f;
	title_anim.loop = false;
	//Blue
	player_blue_rec.x = 0;
	player_blue_rec.y = 0;
	player_blue_rec.w = 240;
	player_blue_rec.h = 320;
	//Copy
	copyr_rec.x = 0;
	copyr_rec.y = 0;
	copyr_rec.w = 240;
	copyr_rec.h = 320;
	//O anim
	Ob_anim.PushBack({ 2, 9, 34, 35 });

	Ob_path.PushBack({ -1, 1 }, 100, &Ob_anim);
	Ob_path.loop = false;
	o.x = 200;
	o.y = 50;
	co.x = 200;
	co.y = 50;

}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading Title scene");
	starttime = SDL_GetTicks();
	chars_tex = App->textures->Load("Outzone/Sprites/Title/title_letters.png");
	title_tex = App->textures->Load("OutZone/Sprites/Title/title_name_anim.png");
	player_blue = App->textures->Load("OutZone/Sprites/Title/BluePlayer.png");
	copyr = App->textures->Load("OutZone/Sprites/Title/OnMenu.png");
	App->player->Disable();
	App->ui->title = true;
	
	
	return true;
}

// UnLoad assets
bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading Title scene");
	App->textures->Unload(title_tex);
	App->textures->Unload(chars_tex);
	App->ui->title = false;

	return true;
}

// Update: draw background
update_status ModuleSceneTitle::Update()
{
	App->render->Blit(player_blue, 0, 0, &player_blue_rec);
	App->render->Blit(title_tex, 15, 88, &title_anim.GetCurrentFrame());

	//App->render->Blit(copyr, 0, 0, &copyr_rec); Copyright thing

	co = o + Ob_path.GetCurrentSpeed();
	App->render->Blit(chars_tex, co.x, co.y, &Ob_anim.GetCurrentFrame());
	// swap Scene
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->ui->credit>0){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		if (no_pay)
			App->ui->SubCoin();
		no_pay = false;
	}
	
	

	return UPDATE_CONTINUE;
}