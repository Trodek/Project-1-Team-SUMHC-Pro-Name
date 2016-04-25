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
	//char O
	chars_rec_o.x = 1;
	chars_rec_o.y = 60;
	chars_rec_o.w = 36;
	chars_rec_o.h = 37;
	//
	//char u
	chars_rec_u.x = 40;
	chars_rec_u.y = 67;
	chars_rec_u.w = 30;
	chars_rec_u.h = 28;
	//
	//char t
	chars_rec_t.x = 74;
	chars_rec_t.y = 57;
	chars_rec_t.w = 48;
	chars_rec_t.h = 43;
	//
	//char z
	chars_rec_z.x = 125;
	chars_rec_z.y = 59;
	chars_rec_z.w = 45;
	chars_rec_z.h = 39;
	//
	//char o2
	chars_rec_o2.x = 173;
	chars_rec_o2.y = 65;
	chars_rec_o2.w = 29;
	chars_rec_o2.h = 33;
	//
	//char n
	chars_rec_n.x = 205;
	chars_rec_n.y = 64;
	chars_rec_n.w = 32;
	chars_rec_n.h = 33;
	//
	//char e
	chars_rec_e.x = 240;
	chars_rec_e.y = 66;
	chars_rec_e.w = 31;
	chars_rec_e.h = 34;
	//
	// Here will be the bright chars

	//char Ob
	chars_rec_ob.x = 1;
	chars_rec_ob.y = 10;
	chars_rec_ob.w = 36;
	chars_rec_ob.h = 38;
	//
	//char ub
	chars_rec_ub.x = 40;
	chars_rec_ub.y = 19;
	chars_rec_ub.w = 30;
	chars_rec_ub.h = 28;
	//
	//char tb
	chars_rec_tb.x = 74;
	chars_rec_tb.y = 6;
	chars_rec_tb.w = 48;
	chars_rec_tb.h = 43;
	//
	//char zb
	chars_rec_zb.x = 125;
	chars_rec_zb.y = 9;
	chars_rec_zb.w = 45;
	chars_rec_zb.h = 39;
	//
	//char o2b
	chars_rec_o2b.x = 173;
	chars_rec_o2b.y = 14;
	chars_rec_o2b.w = 29;
	chars_rec_o2b.h = 33;
	//
	//char nb
	chars_rec_nb.x = 205;
	chars_rec_nb.y = 15;
	chars_rec_nb.w = 32;
	chars_rec_nb.h = 33;
	//
	//char eb
	chars_rec_eb.x = 240;
	chars_rec_eb.y = 15;
	chars_rec_eb.w = 30;
	chars_rec_eb.h = 33;
	//

}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading Title scene");
	chars_tex = App->textures->Load("Outzone/Sprites/Title/title_letters.png");
	title_tex = App->textures->Load("OutZone/Sprites/Title/title_name_anim.png");
	App->player->Disable();
	App->ui->title = true;
	starttime = SDL_GetTicks();
	//Char ob
	obx = 147;
	oby = 358;
	//
	//Char ub
	
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

		//Char o
	if (currenttime<(starttime + 5500)){

		if (currenttime > starttime + 0 && currenttime < starttime + 765){// 30 ticks per sec
			oby -= 6;
			obx -= 3;
			currenttime = SDL_GetTicks();
		}

		App->render->Blit(chars_tex, obx, oby, &chars_rec_ob);
	}
	
	else App->render->Blit(title_tex, 15, 87, &title_anim.GetCurrentFrame());
	// swap Scene
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->ui->credit>0){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		App->ui->SubCoin();
	}
	
	

	return UPDATE_CONTINUE;
}