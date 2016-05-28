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

#define TIME_ELAPSED 916

ModuleSceneTitle::ModuleSceneTitle()
{
	// ground
	title_screen.x = 0;
	title_screen.y = 0;
	title_screen.w = 240;
	title_screen.h = 320;
	//
	Tittleposition.x = 0; 
	Tittleposition.y = 0;
	Tittleposition.w = 200;
	Tittleposition.h = 54;
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

	Ob_path.PushBack({ -4, -5.0f }, 50, &Ob_anim);
	Ob_path.loop = false;
	o.x = 217;
	o.y = 347;

	//U anim
	ub_anim.PushBack({ 39, 16, 31, 29 });

	ub_path.PushBack({ -4, -5.0f }, 50, &Ob_anim);
	ub_path.loop = false;
	u.x = 246;
	u.y = 354;

	//T anim
	tb_anim.PushBack({ 72, 8, 43, 39 });

	tb_path.PushBack({ -4, -5.0f }, 50, &Ob_anim);
	tb_path.loop = false;
	t.x = 264;
	t.y = 346;

	//Z anim
	zb_anim.PushBack({ 118, 9, 39, 37 });

	zb_path.PushBack({ 2, -5.0f }, 50, &Ob_anim);
	zb_path.loop = false;
	z.x = -1;
	z.y = 348;

	//O2 anim
	o2b_anim.PushBack({ 165, 13, 29, 33 });

	o2b_path.PushBack({ 2, -5.0f }, 50, &Ob_anim);
	o2b_path.loop = false;
	o2.x = 31;
	o2.y = 352;

	//n anim
	nb_anim.PushBack({ 201, 12, 32, 33 });

	nb_path.PushBack({ 2, -5.0f }, 50, &Ob_anim);
	nb_path.loop = false;
	n.x = 56;
	n.y = 350;

	//e anim
	eb_anim.PushBack({ 242, 14, 30, 33 });
	eb_anim.PushBack({ 242, 64, 30, 33 });
	eb_anim.speed = 0.1f;

	eb_path.PushBack({ 0, 0 }, 101, &Ob_anim);
	eb_path.loop = false;
	e.x = 184;
	e.y = 100;



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
	App->ui->startgame = false;
	
	return true;
}

// UnLoad assets
bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading Title scene");
	App->textures->Unload(title_tex);
	App->textures->Unload(chars_tex);
	App->ui->title = false;
	no_pay = true;

	return true;
}

// Update: draw background
update_status ModuleSceneTitle::Update()
{
	App->render->Blit(player_blue, 0, 0, &player_blue_rec);

	if (first_time){
		born = SDL_GetTicks();
		first_time = false;
	}
	now = SDL_GetTicks();



	//App->render->Blit(copyr, 0, 0, &copyr_rec); Copyright thing
	if (now - born < TIME_ELAPSED * 6) {
		co = o + Ob_path.GetCurrentSpeed();
		App->render->Blit(chars_tex, co.x, co.y, &Ob_anim.GetCurrentFrame());
	}
	if (now - born > TIME_ELAPSED && now-born < TIME_ELAPSED*6) {
		cz = z + zb_path.GetCurrentSpeed();
		App->render->Blit(chars_tex, cz.x, cz.y, &zb_anim.GetCurrentFrame());
	}
	if (now - born > TIME_ELAPSED * 2 && now - born < TIME_ELAPSED * 6) {
		cu = u + ub_path.GetCurrentSpeed();
		App->render->Blit(chars_tex, cu.x, cu.y, &ub_anim.GetCurrentFrame());
	}
	if (now - born > TIME_ELAPSED * 3 && now - born < TIME_ELAPSED * 6) {
		co2 = o2 + o2b_path.GetCurrentSpeed();
		App->render->Blit(chars_tex, co2.x, co2.y, &o2b_anim.GetCurrentFrame());
	}
	if (now - born > TIME_ELAPSED * 4 && now - born < TIME_ELAPSED * 6) {
		ct = t + tb_path.GetCurrentSpeed();
		App->render->Blit(chars_tex, ct.x, ct.y, &tb_anim.GetCurrentFrame());
	}
	if (now - born > TIME_ELAPSED * 5 && now - born < TIME_ELAPSED * 6) {
		cn = n + nb_path.GetCurrentSpeed();
		App->render->Blit(chars_tex, cn.x, cn.y, &nb_anim.GetCurrentFrame());
	}
	ce = e + eb_path.GetCurrentSpeed();
	App->render->Blit(chars_tex, ce.x, ce.y, &eb_anim.GetCurrentFrame());
	if (now - born > TIME_ELAPSED * 6) {
			App->render->Blit(title_tex, 15, 88, &title_anim.GetCurrentFrame());
	}
	// swap Scene
	if ((App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_SPACE]) && App->ui->credit>0 && no_pay){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		if (no_pay)
			App->ui->SubCoin();
		no_pay = false;
		App->ui->startgame = true;
	}
/*
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN && App->ui->credit > 1 && no_pay) {
		App->ui->player2_enabled = true;
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		if (no_pay) {
			App->ui->SubCoin();
			App->ui->SubCoin();
		}
		no_pay = false;
	}*/
	

	return UPDATE_CONTINUE;
}