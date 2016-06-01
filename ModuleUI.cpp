#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleUI.h"


ModuleUI::ModuleUI(){

	//Player 1 
	player1.PushBack({ 11, 9, 54, 7 });
	player1.PushBack({ 11, 21, 54, 7 });
	player1.speed = 0.01f;

	player1_static.x = 11;
	player1_static.y = 9;
	player1_static.w = 54;
	player1_static.h = 7;

	//Player 2 
	player2.PushBack({ 3, 58, 75, 15 });
	player2.PushBack({ 82, 58, 75, 15 });
	player2.PushBack({ 164, 58, 75, 15 });
	player2.PushBack({ 3, 78, 75, 15 });
	player2.PushBack({ 164, 58, 75, 15 });
	player2.PushBack({ 82, 58, 75, 15 });
	player2.speed = 0.15f;

	player2_title.x = 144;
	player2_title.y = 82;
	player2_title.w = 55;
	player2_title.h = 7;

	//Player 2 ingame
	player2_name.PushBack({ 144, 82, 55, 7 });
	player2_name.PushBack({ 144, 90, 55, 7 });
	player2_name.speed = 0.01f;

	//lives 
	lives_num.x = 17;
	lives_num.y = 35;
	lives_num.w = 8;
	lives_num.h = 15;

	lives_symbol.x = 74;
	lives_symbol.y = 8;
	lives_symbol.w = 8;
	lives_symbol.h = 16;

	//top score

	top_name.x = 206;
	top_name.y = 12;
	top_name.w = 22;
	top_name.h = 7;

	top_points.x = 124;
	top_points.y = 205;
	top_points.w = 7;
	top_points.h = 7;

	//credits

	credits_name.x = 94;
	credits_name.y = 90;
	credits_name.w = 47;
	credits_name.h = 7;

	credits_num.x = 80;
	credits_num.y = 102;
	credits_num.w = 7;
	credits_num.h = 7;

	insert_coin.x = 8;
	insert_coin.y = 323;
	insert_coin.w = 152;
	insert_coin.h = 10;
	
	InsertCoin.PushBack({ 8, 336, 76, 16 });
	InsertCoin.PushBack({ 95, 336, 76, 16 });
	InsertCoin.PushBack({ 8, 355, 76, 16 });
	InsertCoin.PushBack({ 95, 355, 76, 16 });
	InsertCoin.PushBack({ 8, 355, 76, 16 });
	InsertCoin.PushBack({ 95, 336, 76, 16 });
	InsertCoin.speed = 0.4f;

	//energy

	energy_pill.x = 89;
	energy_pill.y = 12;
	energy_pill.w = 1;
	energy_pill.h = 6;

	energy_bar.x = 95;
	energy_bar.y = 11;
	energy_bar.w = 92;
	energy_bar.h = 8;

	energy_bar_p2.x = 95;
	energy_bar_p2.y = 20;
	energy_bar_p2.w = 92;
	energy_bar_p2.h = 8;

	energy_bar_ext.x = 74;
	energy_bar_ext.y = 43;
	energy_bar_ext.w = 116;
	energy_bar_ext.h = 8;

	//bomb
	bomb.x = 213;
	bomb.y = 32;
	bomb.w = 8;
	bomb.h = 16;

	//gameover
	gameover.x = 1;
	gameover.y = 216;
	gameover.w = 194;
	gameover.h = 33;
	
	//low_energy
	Low_energy_static.x = 5;
	Low_energy_static.y = 5;
	Low_energy_static.w = 40;
	Low_energy_static.h = 24;

	//Stage Clear
	stageclear.x = 0;
	stageclear.y = 378;
	stageclear.w = 118;
	stageclear.h = 37;

	bombpoints.x = 119;
	bombpoints.y = 378;
	bombpoints.w = 120;
	bombpoints.h = 87;

	pink_numbers.x = 5;
	pink_numbers.y = 472;
	pink_numbers.w = 7;
	pink_numbers.h = 7;

	bomb_cont.x = 2;
	bomb_cont.y = 493;
	bomb_cont.w = 12;
	bomb_cont.h = 18;
	//CheckPoints
	checkpoints.PushBack(-7159 * SCREEN_SIZE);
	checkpoints.PushBack(-7000 * SCREEN_SIZE);
	checkpoints.PushBack(-5965 * SCREEN_SIZE);
	checkpoints.PushBack(-4900 * SCREEN_SIZE);
	checkpoints.PushBack(-2775 * SCREEN_SIZE);
	checkpoints.PushBack(-2000 * SCREEN_SIZE);
	checkpoints.PushBack(-471 * SCREEN_SIZE);

	char* rank1 = new char[3] { '?', '?', '?' };
	char* rank2 = new char[3] { '?', '?', '?' };
	char* rank3 = new char[3] { '?', '?', '?' };
	char* rank4 = new char[3] { '?', '?', '?' };
	char* rank5 = new char[3] { '?', '?', '?' };
	TopScores.PushBack({ rank1, 0, 200000 });
	TopScores.PushBack({ rank2, 0, 100000 });
	TopScores.PushBack({ rank3, 0, 50000 });
	TopScores.PushBack({ rank4, 0, 20000 });
	TopScores.PushBack({ rank5, 0, 10000 });

	top_score = TopScores[0].Tscore;
	get_score = false;
}

ModuleUI::~ModuleUI(){}

bool ModuleUI::Start(){

	ui_graphics = App->textures->Load("OutZone/Sprites/Interface/ui_stuff.png");
	low_energy = App->textures->Load("Outzone/Sprites/Main Char/Energy_dead_char.png");
	coin_sound = App->audio->LoadSoundEffect("OutZone/Sounds/Effects/insert coin.wav");

	return true;
}

bool ModuleUI::CleanUp(){
	App->textures->Unload(low_energy);
	App->textures->Unload(ui_graphics);
	for (int i = 0; i < 5; i++) {
		if (TopScores[i].name != nullptr) {
			delete[] TopScores[i].name;
			TopScores[i].name = nullptr;
		}
	}
	return true;
}

update_status ModuleUI::Update(){

	now = SDL_GetTicks();

	if (App->input->keyboard[SDL_SCANCODE_5] == KEY_STATE::KEY_DOWN){
		App->ui->AddCoin();
	}

	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN){
		App->ui->AddEnergy();
	}

	if (game){

		if (dead){
			lives--;
			if (lives >= 0){
				dead = false;
				App->player->position.x = checkpoints[curr_check].x;
				App->player->position.y = checkpoints[curr_check].y;
				App->player->PlayerCollider->SetPos(App->player->position.x + 10, App->player->position.y + 20);
				App->player->PlayerEBulletsCollider->SetPos(App->player->position.x + 4, App->player->position.y + 3);
				App->player->speedup = false;
				App->player->last_basic_weapon = MULTI;
				App->player->current_weapon = LASER;
				App->player->current_power = P0;
				App->player->dead = false;
				App->player->speed = 2;
				App->player->shield = false;
				App->player->fall_hole.Reset();
				App->player->direction = IDLE;
				App->render->camera.y = checkpoints[curr_check].camera_y;
				ResetEnergyBombs();
				App->player->dead_explo.Reset();
				App->player->out_of_energy.Reset();
				energy = 36;
				max_energy = 36;
			}
			else {
				//App->render->Blit(ui_graphics, 23, (-App->render->camera.y) / SCREEN_SIZE + 136, &gameover);
				if (TopScore())
					App->fade->FadeToBlack((Module *)App->levels, (Module *)App->namescreen, 1.0f);
				else
					App->fade->FadeToBlack((Module *)App->levels, (Module *)App->losescreen, 1.0f);
				App->player->dead_explo.Reset();
			}

		}

		if (score > top_score) top_score = score;
		if (now - e_timer > 1500 && energy > 0) {
			energy--;
			energy_p2--;
			e_timer = SDL_GetTicks();	
			if (energy == 0) 
				App->player->SetEnergyDeath();
		}
	
		if (curr_check + 1 < checkpoints.size()){
			if ((-App->render->camera.y) / 3 + 200 < checkpoints[curr_check + 1].y)
				curr_check++;
		}

		/*---------------------- PLAYER 1 ----------------------*/
		App->render->Blit(ui_graphics, 26, (-App->render->camera.y) / SCREEN_SIZE + 1, &(player1.GetCurrentFrame()));			//player1 name
		DrawNumber(score, 74, (-App->render->camera.y) / SCREEN_SIZE + 9, 8, top_points);										//player score

		App->render->Blit(ui_graphics, 0, (-App->render->camera.y) / SCREEN_SIZE, &lives_symbol);								//lives icon
		DrawNumber(lives, 8, (-App->render->camera.y) / SCREEN_SIZE + 1, 8, lives_num);											//lives number

		if (max_energy == 36)
			App->render->Blit(ui_graphics, 0, (-App->render->camera.y) / SCREEN_SIZE + 17, &energy_bar);							//energy bar
		else
			App->render->Blit(ui_graphics, 0, (-App->render->camera.y) / SCREEN_SIZE + 17, &energy_bar_ext);

		for (int i = 0; i < energy; i++)
			App->render->Blit(ui_graphics, 17 + (2 * i), (-App->render->camera.y) / SCREEN_SIZE + 18, &energy_pill);			//fill the bar
		for (int i = 0; i < bombs; i++)																				
			App->render->Blit(ui_graphics, 8 * i, (-App->render->camera.y) / SCREEN_SIZE + 304, &bomb);							//bombs

		if (!(energy % 2) && energy < 7) {
			App->render->Blit(low_energy, 8, (-App->render->camera.y) / SCREEN_SIZE + 27, &Low_energy_static);					//Low energy
		}

		/*---------------------- TOP SCORE ----------------------*/
		App->render->Blit(ui_graphics, 105, (-App->render->camera.y) / SCREEN_SIZE + 1, &top_name);								//top name
		DrawNumber(top_score, 137, (-App->render->camera.y) / SCREEN_SIZE + 9, 8, top_points);									//top score

		/*---------------------- PLAYER 2 ----------------------*/
		if (player2_enabled) {
			App->render->Blit(ui_graphics, 158, (-App->render->camera.y) / SCREEN_SIZE + 1, &(player2_name.GetCurrentFrame()));	//player2 name
			DrawNumber(score_p2, 206, (-App->render->camera.y) / SCREEN_SIZE + 9, 8, top_points);								//player2 score

			App->render->Blit(ui_graphics, 164 + 59, (-App->render->camera.y) / SCREEN_SIZE, &lives_symbol);					//lives icon
			DrawNumber(lives_p2, 164 + 57 + 10, (-App->render->camera.y) / SCREEN_SIZE + 1, 9, lives_num);						//lives number

			App->render->Blit(ui_graphics, 148, (-App->render->camera.y) / SCREEN_SIZE + 17, &energy_bar_p2);					//energy bar
			for (int i = 0; i < energy; i++) 
				App->render->Blit(ui_graphics, 164 + 58 - (2 * i), (-App->render->camera.y) / SCREEN_SIZE + 18, &energy_pill);	//fill the bar
			for (int i = 0; i < bombs_p2;  i++)																					
				App->render->Blit(ui_graphics, 232 - (8 * i), (-App->render->camera.y) / SCREEN_SIZE + 304, &bomb);				//bombs

			if (!(energy % 2) && energy < 7) {
				App->render->Blit(low_energy, 190, (-App->render->camera.y) / SCREEN_SIZE + 27, &Low_energy_static);			//Low energy
			}
		}
		else
			App->render->Blit(ui_graphics, 160, (-App->render->camera.y) / SCREEN_SIZE + 1, &(player2.GetCurrentFrame()));		//player2
		if (get_score) {
			App->render->Blit(ui_graphics, 60, 60, &stageclear);
			App->render->Blit(ui_graphics, 60, 110, &bombpoints);
			DrawNumber(bombs, 158, 136, 8, bomb_cont);
			DrawNumber(50000, 112, 163, 8, pink_numbers);
			DrawNumber(temp_bomb, 112, 179, 8, pink_numbers);
			if ((temp_bomb - 100) >= 0) temp_bomb -= 100;
			else {
				temp_bomb = 0;
				App->fade->FadeToBlack((Module*)App->levels, (Module*)App->winscreen, 4.0f);
			}
		}
	}
	else{
		//Draw Stuff
			

		App->render->Blit(ui_graphics, 164, 1, &player2_title);															//player2
		DrawNumber(score_p2, 212, 9, 8, top_points);																	//player2 score

		App->render->Blit(ui_graphics, 105, 1, &top_name);																//top
		DrawNumber(top_score, 137, (-App->render->camera.y) / SCREEN_SIZE + 9, 8, top_points);							//top score

		if (title || cont){
			App->render->Blit(ui_graphics, 84, 305, &credits_name);														//credits
			DrawNumber(credit, 140, 305, 10, credits_num);																//credit number
		}	
		if (title || cont) {
			if (credit == 0 && !startgame) {
				App->render->Blit(ui_graphics, 10, 1, &(InsertCoin.GetCurrentFrame()));
			}
			else {
				App->render->Blit(ui_graphics, 26, 1, &player1_static);													//player1
				DrawNumber(score, 74, (-App->render->camera.y) / SCREEN_SIZE + 9, 8, top_points);						//player score
			}
		}
		else {
			App->render->Blit(ui_graphics, 26, 1, &player1_static);														//player1						
			DrawNumber(score, 74, (-App->render->camera.y) / SCREEN_SIZE + 9, 8, top_points);							//player score	
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleUI::SetGameStartConditions(){
	lives = 2;
	if (!get_score) 
		score = 0;
	else {
		score = temp_score;
		get_score = false;
	}
	first_time = true;
	temp_score = 0;
	energy = 36;
	max_energy = 36;
	bombs = 3;
	game = true;
	curr_check = 0;
	dead = false;
	if (player2_enabled) {
		lives_p2 = 2;
		score_p2 = 0;
		bombs_p2 = 3;
		player2_dead = false;
	}
}

void ModuleUI::DrawNumber(int number, int x, int y, int variable, SDL_Rect Points) {
	int aux;
	if (number == 0) {
		App->render->Blit(App->ui->ui_graphics, x, y, &Points);
	}
	else {
		for (int j = 0, temp_score = number; j <= 7 && temp_score > 0; j++, temp_score /= 10) {
			aux = temp_score % 10;
			Points.x += aux * 12;
			App->render->Blit(App->ui->ui_graphics, x - variable * j, y, &Points);
			Points.x -= aux * 12;
		}
	}
}

void ModuleUI::AddCoin(){
	if (credit<9){ 
		credit++;
		App->audio->PlaySoundEffect(coin_sound);
	}
}

void ModuleUI::SubCoin(){
	if (credit>0) credit--;
}

void ModuleUI::AddBomb(){
	if (bombs < 10) bombs++;
}

void ModuleUI::SubBomb(char player){
	switch (player) {
	case 1:
		if (bombs > 0) bombs--;
	case 2:
		if (bombs > 0) bombs_p2--;
	}

}

void ModuleUI::AddEnergy(){
	energy += 15;
	energy_p2 += 15;
	if (energy > max_energy) energy = max_energy;
	if (energy_p2 > max_energy) energy_p2 = max_energy;
}

void ModuleUI::ResetEnergyBombs(){
	energy = max_energy;
	bombs = 3;
}

bool ModuleUI::TopScore() {
	for (int i = 0; i < 5; i++)
	if (score > TopScores[i].Tscore)
		return true;
	return false;
}

void ModuleUI::GetScore() {
	temp_score = score;
	get_score = true;
	temp_bomb = bombs * 1500;
	score += temp_bomb;
	first_time = false;
}