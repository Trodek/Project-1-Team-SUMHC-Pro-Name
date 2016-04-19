#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleUI.h"

ModuleUI::ModuleUI(){

	//Player 1 
	player1.PushBack({ 11, 9, 54, 7 });
	player1.PushBack({ 11, 21, 54, 7 });
	player1.speed = 0.05f;
	
	player1_static.x = 11;
	player1_static.y = 9;
	player1_static.w = 54;
	player1_static.h = 7;

	//Player 2 
	player2.PushBack({ 3, 58, 75, 15 });
	player2.PushBack({ 82, 58, 75, 15 });
	player2.PushBack({ 164, 58, 75, 15 });
	player2.PushBack({ 3, 78, 75, 15 });

	player2_title.x = 89;
	player2_title.y = 78;
	player2_title.w = 55;
	player2_title.h = 7;

	//score numbers
	num0.x = 83;
	num0.y = 29;
	num0.w = 7;
	num0.h = 7;

	num1.x = 92;
	num1.y = 29;
	num1.w = 7;
	num1.h = 7;

	num2.x = 104;
	num2.y = 29;
	num2.w = 7;
	num2.h = 7;

	num3.x = 116;
	num3.y = 29;
	num3.w = 7;
	num3.h = 7;

	num4.x = 128;
	num4.y = 29;
	num4.w = 7;
	num4.h = 7;

	num5.x = 140;
	num5.y = 29;
	num5.w = 7;
	num5.h = 7;

	num6.x = 152;
	num6.y = 29;
	num6.w = 7;
	num6.h = 7;

	num7.x = 164;
	num7.y = 29;
	num7.w = 7;
	num7.h = 7;

	num8.x = 176;
	num8.y = 29;
	num8.w = 7;
	num8.h = 7;

	num9.x = 188;
	num9.y = 29;
	num9.w = 7;
	num9.h = 7;

	//lives numbers
	lives0.x = 17;
	lives0.y = 35;
	lives0.w = 8;
	lives0.h = 15;

	lives1.x = 30;
	lives1.y = 35;
	lives1.w = 8;
	lives1.h = 15;

	lives2.x = 46;
	lives2.y = 35;
	lives2.w = 8;
	lives2.h = 15;

	//lives symbol
	lives_symbol.x = 74;
	lives_symbol.y = 8;
	lives_symbol.w = 8;
	lives_symbol.h = 16;

	//energy
	energy_pill.x = 89;
	energy_pill.y = 12;
	energy_pill.w = 1;
	energy_pill.h = 6;

	energy_bar.x = 95;
	energy_bar.y = 11;
	energy_bar.w = 92;
	energy_bar.h = 8;
		   
	energy_bar_ext.x = 74;
	energy_bar_ext.y = 43;
	energy_bar_ext.w = 116;
	energy_bar_ext.h = 8;

	//Top
	top.x = 206;
	top.y = 12;
	top.w = 22;
	top.h = 7;

	//bomb
	top.x = 213;
	top.y = 32;
	top.w = 8;
	top.h = 16;

	//credits
	credits.x = 94;
	credits.y = 90;
	credits.w = 47;
	credits.h = 7;

	c0.x = 83;
	c0.y = 102;
	c0.w = 7;
	c0.h = 7;
	
	c1.x = 92;
	c1.y = 102;
	c1.w = 7;
	c1.h = 7;
	
	c2.x = 104;
	c2.y = 102;
	c2.w = 7;
	c2.h = 7;
	
	c3.x = 116;
	c3.y = 102;
	c3.w = 7;
	c3.h = 7;
	
	c4.x = 128;
	c4.y = 102;
	c4.w = 7;
	c4.h = 7;
	
	c5.x = 140;
	c5.y = 102;
	c5.w = 7;
	c5.h = 7;
	
	c6.x = 152;
	c6.y = 102;
	c6.w = 7;
	c6.h = 7;
	
	c7.x = 164;
	c7.y = 102;
	c7.w = 7;
	c7.h = 7;
	
	c8.x = 176;
	c8.y = 102;
	c8.w = 7;
	c8.h = 7;
	
	c9.x = 188;
	c9.y = 102;
	c9.w = 7;
	c9.h = 7;
	
}

ModuleUI::~ModuleUI(){}

bool ModuleUI::Start(){

	ui_graphics = App->textures->Load("OutZone/Sprites/Interface/ui_stuff.png");
	score1 = &num0;
	c_num = &c0;
	p2_score = &num0;
	return true;
}

bool ModuleUI::CleanUp(){
	return true;
}

update_status ModuleUI::Update(){

	if (game){

	}
	else{

	}

	return UPDATE_CONTINUE;
}

void ModuleUI::SetGameStartConditions(){

	lives = 2;
	score = 0;
	energy = 36;
	max_energy = 36;
	bombs = 3;
	born = SDL_GetTicks();
	game = true;
	lives_num = &lives2;

}