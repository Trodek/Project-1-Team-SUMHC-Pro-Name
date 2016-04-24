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
	//
	chars_rec_o.x = 0;
	chars_rec_o.y = 0;
	chars_rec_o.w = 72;
	chars_rec_o.h = 66;
}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading Title scene");
	chars_tex = App->textures->Load("Outzone/Sprites/Title/title_letterss.png");
	title_tex = App->textures->Load("OutZone/Sprites/Title/title_name_anim.png");
	App->player->Disable();
	App->ui->title = true;
	starttime = SDL_GetTicks();
	//Char o
	ox = 30;
	oy = 200;
	//
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
	int currenttime = SDL_GetTicks();
	// Draw everything --------------------------------------
	App->render->Blit(title_tex, 17, 89, &title_anim.GetCurrentFrame()); // background
	
	//Char o
	if (currenttime > starttime + 0 && currenttime < starttime + 1000){
		oy -= 2;
		ox += 1;
	}
	
	App->render->Blit(chars_tex, ox, oy, &chars_rec_o);
	//

	// swap Scene
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->ui->credit>0){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		App->ui->SubCoin();
	}
	


	return UPDATE_CONTINUE;
}