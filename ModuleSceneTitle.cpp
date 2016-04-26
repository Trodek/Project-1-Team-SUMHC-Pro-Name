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
	e_anim.PushBack({ 241, 15, 31, 34 });
	e_anim.PushBack({ 240, 66, 31, 34 });
	e_anim.speed = 0.08f;
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
	
	//Char ob
	obx = 177;
	oby = 365;
	//
	//Char ub
	ubx = 141;
	uby = 362;
	//
	//Char tb
	tbx = 230;
	tby = 374;
	//
	//Char zb
	zbx = -12;
	zby = 370 + 5;
	//
	//Char o2b
	o2bx = 66;
	o2by = 332+5;
	//
	//Char o2b
	nbx = 65;
	nby = 386 + 5;
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
	App->render->Blit(player_blue, 0, 0, &player_blue_rec);
	int currenttime = SDL_GetTicks();

		//Char o
	if (currenttime<(starttime + 5000)){

		App->render->Blit(chars_tex, 193, 92, &e_anim.GetCurrentFrame());

		if (currenttime > starttime + 0 && currenttime < starttime + 916){// 30 ticks per sec
			oby -= 5;
			obx -= 3;
		}
		App->render->Blit(chars_tex, obx, oby, &chars_rec_ob);

		if (currenttime > starttime + 916 && currenttime < starttime + 1832){// 30 ticks per sec
			zby -= 5;
			zbx += 2;
		}
		App->render->Blit(chars_tex, zbx, zby, &chars_rec_zb);

		if (currenttime > starttime + 1832 && currenttime < starttime + 2355){// 30 ticks per sec
			uby -= 8;
			ubx -= 3;
		}
		App->render->Blit(chars_tex, ubx, uby, &chars_rec_ub);

		if (currenttime > starttime + 2355 && currenttime < starttime + 2748){// 30 ticks per sec
			o2by -= 10;
			o2bx += 3;
		}
		App->render->Blit(chars_tex, o2bx, o2by, &chars_rec_o2b);

		if (currenttime > starttime + 2748 && currenttime < starttime + 3664){// 30 ticks per sec
			tby -= 5;
			tbx -= 3;
		}
		App->render->Blit(chars_tex, tbx, tby, &chars_rec_tb);

		if (currenttime > starttime + 3664 && currenttime < starttime + 4449){// 30 ticks per sec
			nby -= 6;
			nbx += 2;

		}
		App->render->Blit(chars_tex, nbx, nby, &chars_rec_nb);

	}
	
	else App->render->Blit(title_tex, 15, 88, &title_anim.GetCurrentFrame());

	//App->render->Blit(copyr, 0, 0, &copyr_rec); Copyright thing

	// swap Scene
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->ui->credit>0){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		App->ui->SubCoin();
	}
	
	

	return UPDATE_CONTINUE;
}