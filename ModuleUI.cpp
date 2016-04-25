#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
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
	bomb.x = 213;
	bomb.y = 32;
	bomb.w = 8;
	bomb.h = 16;

	//gameover
	gameover.x = 1;
	gameover.y = 216;
	gameover.w = 194;
	gameover.h = 33;

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
	
	//CheckPoints
	checkpoints.PushBack(-15063 * SCREEN_SIZE);
	checkpoints.PushBack(-14000 * SCREEN_SIZE);
	checkpoints.PushBack(-13050 * SCREEN_SIZE);
	checkpoints.PushBack(-12200 * SCREEN_SIZE);
	checkpoints.PushBack(-11917 * SCREEN_SIZE);
	checkpoints.PushBack(-11205 * SCREEN_SIZE);
	checkpoints.PushBack(-10519 * SCREEN_SIZE);
	checkpoints.PushBack(-9135 * SCREEN_SIZE);
	checkpoints.PushBack(-8133 * SCREEN_SIZE);
	checkpoints.PushBack(-6481 * SCREEN_SIZE);
	checkpoints.PushBack(-5965 * SCREEN_SIZE);
	checkpoints.PushBack(-4900 * SCREEN_SIZE);
	checkpoints.PushBack(-2775 * SCREEN_SIZE);
	checkpoints.PushBack(-1347 * SCREEN_SIZE);

	rank1 = new char[3] { ' ', ' ', ' ' };
	rank2 = new char[3] { ' ', ' ', ' ' };
	rank3 = new char[3] { ' ', ' ', ' ' };
	rank4 = new char[3] { ' ', ' ', ' ' };
	rank5 = new char[3] { ' ', ' ', ' ' };
	TopScores.PushBack({ rank1, 0, 200000 });
	TopScores.PushBack({ rank2, 0, 100000 });
	TopScores.PushBack({ rank3, 0, 50000 });
	TopScores.PushBack({ rank4, 0, 20000 });
	TopScores.PushBack({ rank5, 0, 10000 });

	top_score = TopScores[0].Tscore;
}

ModuleUI::~ModuleUI(){}

bool ModuleUI::Start(){

	ui_graphics = App->textures->Load("OutZone/Sprites/Interface/ui_stuff.png");
	score1 = &num0;
	c_num = &c0;
	p2_score = &num0;
	UpdateTopScorenums();
	return true;
}

bool ModuleUI::CleanUp(){

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

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN){
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
				App->player->dead = false;
				App->player->fall_hole.Reset();
				App->player->direction = IDLE;
				App->render->camera.y = checkpoints[curr_check].camera_y;
				RestetEnergyBombs();
				App->player->dead_explo.Reset();
			}
			else {
				App->render->Blit(ui_graphics, 23, (-App->render->camera.y) / SCREEN_SIZE + 136, &gameover);
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
			e_timer = SDL_GetTicks();
		}

		if (curr_check + 1 < checkpoints.size()){
			if ((-App->render->camera.y) / 3+200 < checkpoints[curr_check + 1].y)
				curr_check++;
		}

		UpdateScorenums();
		UpdateTopScorenums();
		UpdateLivesnums();

		App->render->Blit(ui_graphics, 18, (-App->render->camera.y) / SCREEN_SIZE + 1, &(player1.GetCurrentFrame()));//player1
		DrawPlayerScore(); //player score

		App->render->Blit(ui_graphics, 158, (-App->render->camera.y) / SCREEN_SIZE + 1, &(player2.GetCurrentFrame()));
		App->render->Blit(ui_graphics, 105, (-App->render->camera.y) / SCREEN_SIZE + 1, &top);//top
		DrawTopScore(); //top score

		for (int i = 0; i < bombs; i++){//bombs
			App->render->Blit(ui_graphics, 8 * i, (-App->render->camera.y) / SCREEN_SIZE + 304, &bomb);
		}

		App->render->Blit(ui_graphics, 0, (-App->render->camera.y) / SCREEN_SIZE, &lives_symbol);// lives icon
		App->render->Blit(ui_graphics, 8, (-App->render->camera.y) / SCREEN_SIZE + 1, lives_num);//lives num

		App->render->Blit(ui_graphics, 0, (-App->render->camera.y) / SCREEN_SIZE + 17, &energy_bar);//energy bar

		for (int i = 0; i < energy; i++){
			App->render->Blit(ui_graphics, 17+(2 * i), (-App->render->camera.y) / SCREEN_SIZE + 18, &energy_pill);
		}

	}
	else{
		UpdateCreditnum();

		//Draw Stuff
		App->render->Blit(ui_graphics, 18, 1, &player1_static);//player1
		DrawPlayerScore(); //player score

		App->render->Blit(ui_graphics, 158, 1, &player2_title);//player2
		App->render->Blit(ui_graphics, 206, 9, p2_score);//p2 score

		App->render->Blit(ui_graphics, 105, 1, &top);//top
		DrawTopScore(); //top score

		if (title||cont){
			App->render->Blit(ui_graphics, 84, 305, &credits);//credits
			App->render->Blit(ui_graphics, 140, 305, c_num);//credit number
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleUI::SetGameStartConditions(){

	lives = 2;
	score = 150001;
	energy = 36;
	max_energy = 36;
	bombs = 3;
	game = true;
	lives_num = &lives2;
	curr_check = 0;
	dead = false;

}

void ModuleUI::UpdateScorenums(){
	int tempscore = score;
	score1 = GetCorrectNum(tempscore%10);
	tempscore /= 10;
	if (score >= 10){
		score10 = GetCorrectNum(tempscore % 10);
		tempscore /= 10;
		if (score >= 100){
			score100 = GetCorrectNum(tempscore % 10);
			tempscore /= 10;
			if (score >= 1000){
				score1000 = GetCorrectNum(tempscore % 10);
				tempscore /= 10;
				if (score >= 10000){
					score10000 = GetCorrectNum(tempscore % 10);
					tempscore /= 10;
					if (score >= 100000){
						score100000 = GetCorrectNum(tempscore % 10);
						tempscore /= 10;
						if (score>=1000000)
							score1000000 = GetCorrectNum(tempscore % 10);
					}
				}
			}
		}
	}
}

void ModuleUI::UpdateTopScorenums(){
	int tempscore = top_score;
	topscore1 = GetCorrectNum(tempscore % 10);
	tempscore /= 10;
	topscore10 = GetCorrectNum(tempscore % 10);
	tempscore /= 10;
	topscore100 = GetCorrectNum(tempscore % 10);
	tempscore /= 10;
	topscore1000 = GetCorrectNum(tempscore % 10);
	tempscore /= 10;
	topscore10000 = GetCorrectNum(tempscore % 10);
	tempscore /= 10;
	topscore100000 = GetCorrectNum(tempscore % 10);
	tempscore /= 10;
	if (top_score>=1000000)
		topscore1000000 = GetCorrectNum(tempscore % 10);
}

void ModuleUI::UpdateCreditnum(){
	switch (credit)
	{
	case 0:
		c_num = &c0;
		break;
	case 1:
		c_num = &c1;
		break;
	case 2:
		c_num = &c2;
		break;
	case 3:
		c_num = &c3;
		break;
	case 4:
		c_num = &c4;
		break;
	case 5:
		c_num = &c5;
		break;
	case 6:
		c_num = &c6;
		break;
	case 7:
		c_num = &c7;
		break;
	case 8:
		c_num = &c8;
		break;
	case 9:
		c_num = &c9;
		break;

	}
}

SDL_Rect* ModuleUI::GetCorrectNum(const int& num){
	switch (num)
	{
	case 0:
		return &num0;
		break;
	case 1:
		return &num1;
		break;
	case 2:
		return &num2;
		break;
	case 3:
		return &num3;
		break;
	case 4:
		return &num4;
		break;
	case 5:
		return &num5;
		break;
	case 6:
		return &num6;
		break;
	case 7:
		return &num7;
		break;
	case 8:
		return &num8;
		break;
	case 9:
		return &num9;
		break;
	}
}

void ModuleUI::DrawPlayerScore(){
	if (score1 != nullptr){
		App->render->Blit(ui_graphics, 66, (-App->render->camera.y) / SCREEN_SIZE + 9, score1);
		if (score10 != nullptr){
			App->render->Blit(ui_graphics, 58, (-App->render->camera.y) / SCREEN_SIZE + 9, score10);
			if (score100 != nullptr){
				App->render->Blit(ui_graphics, 50, (-App->render->camera.y) / SCREEN_SIZE + 9, score100);
				if (score1000 != nullptr){
					App->render->Blit(ui_graphics, 42, (-App->render->camera.y) / SCREEN_SIZE + 9, score1000);
					if (score10000 != nullptr){
						App->render->Blit(ui_graphics, 34, (-App->render->camera.y) / SCREEN_SIZE + 9, score10000);
						if (score100000 != nullptr){
							App->render->Blit(ui_graphics, 26, (-App->render->camera.y) / SCREEN_SIZE + 9, score100000);
							if (score1000000 != nullptr){
								App->render->Blit(ui_graphics, 18, (-App->render->camera.y) / SCREEN_SIZE + 9, score1000000);
							}
						}
					}
				}
			}
		}
	}

}

void ModuleUI::DrawTopScore(){
	if (topscore1 != nullptr){
		App->render->Blit(ui_graphics, 137, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore1);
		if (topscore10 != nullptr){
			App->render->Blit(ui_graphics, 129, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore10);
			if (topscore100 != nullptr){
				App->render->Blit(ui_graphics, 121, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore100);
				if (topscore1000 != nullptr){
					App->render->Blit(ui_graphics, 113, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore1000);
					if (topscore10000 != nullptr){
						App->render->Blit(ui_graphics, 105, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore10000);
						if (topscore100000 != nullptr){
							App->render->Blit(ui_graphics, 97, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore100000);
							if (topscore1000000 != nullptr){
								App->render->Blit(ui_graphics, 89, (-App->render->camera.y) / SCREEN_SIZE + 9, topscore1000000);
							}
						}
					}
				}
			}
		}
	}
}

void ModuleUI::AddCoin(){
	if (credit<9) credit++;
}

void ModuleUI::SubCoin(){
	if(credit>0) credit--;
}

void ModuleUI::UpdateLivesnums(){
	switch (lives){
	case 0: lives_num = &lives0;
		break;
	case 1: lives_num = &lives1;
		break;
	case 2: lives_num = &lives2;
		break;
	}
}

void ModuleUI::AddBomb(){
	if (bombs < 10)bombs++;
}

void ModuleUI::SubBomb(){
	if (bombs > 0)bombs--;
}

void ModuleUI::AddEnergy(){
	energy += 15;
	if (energy > max_energy) energy = max_energy;
}

void ModuleUI::RestetEnergyBombs(){
	energy = max_energy;
	bombs = 3;
}

bool ModuleUI::TopScore() {
	for (int i = 0; i < 5; i++)
		if (score > TopScores[i].Tscore)
			return true;
	return false;
}