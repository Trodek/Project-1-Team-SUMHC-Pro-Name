#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleScoreScreen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleNameScreen.h"
#include "ModuleUI.h"




ModuleScoreScreen::ModuleScoreScreen()
{
	// ground
	score_screen.x = 0;
	score_screen.y = 0;
	score_screen.w = 240;
	score_screen.h = 320;

	//Position
	position.x = 151;
	position.y = 155;
	position.w = 24;
	position.h = 8;

	//Name
	name.x = 6;
	name.y = 258;
	name.w = 8;
	name.h = 8;

	//Score
	score.x = 124;
	score.y = 205;
	score.w = 7;
	score.h = 7;
}

ModuleScoreScreen::~ModuleScoreScreen()
{}

// Load assets
bool ModuleScoreScreen::Start()
{
	LOG("Loading ScoreScreen");
	bool ret = true;
	graphics = App->textures->Load("OutZone/Sprites/Scores/Ranking.png");

	keyboard = new char[6] { '.', '!', '$', '&', '?', '#' };

	return true;
}

// UnLoad assets
bool ModuleScoreScreen::CleanUp()
{
	LOG("Unloading ScoreScreen");
	App->textures->Unload(graphics);
	if (keyboard != nullptr) {
		delete[] keyboard;
		keyboard = nullptr;
	}


	return true;
}

// Update: draw background
update_status ModuleScoreScreen::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &score_screen, 0.75f); // background
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		if (App->ui->TopScore()) 
			App->fade->FadeToBlack(this, (Module*)App->continuescreen, 0.5f);
		else 
			App->fade->FadeToBlack(this, (Module*)App->title, 0.5f);
	}

	for (int i = 0; i < 5; i++) {
		//Draw 1st, 2nd, 3rd, 4th, 5th
		App->render->Blit(App->ui->ui_graphics, 25, 70 + 32 * i, &position);
		App->ui->DrawNumber(App->ui->TopScores[i].area, 82, 70 + 32 * i, 8, (App->namescreen->Points));
		App->render->Blit(App->ui->ui_graphics, 90, 70 + 32 * i, &(App->namescreen->percent));
		position.y += 8;
		//Draw the names
		for (int j = 0; j < 3; j++) {
			if (App->ui->TopScores[i].name[j] <= 'Z' && App->ui->TopScores[i].name[j] >= 'A')
				aux = App->ui->TopScores[i].name[j] - 'A';
			else if (App->ui->TopScores[i].name[j] <= '9' && App->ui->TopScores[i].name[j] >= '0')
				aux = 'Z' - 'A' + (App->ui->TopScores[i].name[j] - '0') + 1;
			else {
				for (aux = 0; App->ui->TopScores[i].name[j] != keyboard[aux]; aux++);
				aux += 'Z' - 'A' + 11;
			}
			y = aux / 11;
			x = aux % 11;
			name.x += 16 * x;
			name.y += 16 * y;
			App->render->Blit(App->ui->ui_graphics, 56 + 16 * j, 70 + 32 * i, &name);
			name.x = 6;
			name.y = 258;
		}
		//Draw the score
		for (int j = 0, temp_score = App->ui->TopScores[i].Tscore; j <= 7 && temp_score > 0; j++, temp_score /= 10) {
			aux = temp_score % 10;
			score.x += aux * 12;
			App->render->Blit(App->ui->ui_graphics, 206 - 8 * j, 70 + 32 * i, &score);
			score.x = 124;
		}
	}
	position.y = 155;



	return UPDATE_CONTINUE;
}




