#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleNameScreen.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleNameScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleUI.h"
#include "dynArray.h"


ModuleNameScreen::ModuleNameScreen()
{
	// ground
	name_screen.x = 0;
	name_screen.y = 0;
	name_screen.w = 240;
	name_screen.h = 320;

	//Square
	square.PushBack({ 147, 116, 16, 16 });
	square.PushBack({ 147, 134, 16, 16 });
	square.speed = 0.2f;

	//layout
	layout.x = 16;
	layout.y = 88;
	layout.w = 209;
	layout.h = 168;
}

ModuleNameScreen::~ModuleNameScreen()
{}

// Load assets
bool ModuleNameScreen::Start()
{
	LOG("Loading name Screen");
	//bool ret = true;
	graphics = App->textures->Load("OutZone/Sprites/Scores/EnterNameBackground.png");
	layout_graphic = App->textures->Load("Outzone/Sprites/Scores/Keyboard.png");
	music = App->audio->LoadMusic("OutZone/Sounds/Music/namescene.ogg");

	for (rank = 0; App->ui->TopScores[rank].Tscore > App->ui->score; rank++);
	for (int i = 0; i < 5; i++) {
		LOG("BEFORE UPDATE %d %c%c%c %d %d", i, App->ui->TopScores[i].name[0], App->ui->TopScores[i].name[1], App->ui->TopScores[i].name[2], App->ui->TopScores[i].area, App->ui->TopScores[i].Tscore);
	}
	UpdateScores();
	App->ui->TopScores[rank].Tscore = App->ui->score;
	App->ui->TopScores[rank].area = (App->ui->curr_check / 14) * 100;
	for (int i = 0; i < 5; i++) {
		LOG("AFTER UPDATE %d %c%c%c %d %d", i, App->ui->TopScores[i].name[0], App->ui->TopScores[i].name[1], App->ui->TopScores[i].name[2], App->ui->TopScores[i].area, App->ui->TopScores[i].Tscore);
	}


	App->audio->PlayMusic(music,LOOP);
	//Square Position
	square_x = 28;
	square_y = 165;

	//Keyboard starting point
	x = 0;
	y = 0;

	//InputName()
	letter = 0;

	//Keyboard
	keyboard = new char[44]
	{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', '.', '!', '$', '&', '?', '#', '<', '/' };
	return true;
}

// UnLoad assets
bool ModuleNameScreen::CleanUp()
{
	LOG("Unloading name scene");
	if (keyboard != nullptr) {
		delete[] keyboard;
		keyboard = nullptr;
	}
	
	App->textures->Unload(graphics);
	App->audio->StopAudio();
	App->audio->UnloadMusic(music);

	return true;
}

// Update: draw background
update_status ModuleNameScreen::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &name_screen, 0.75f); // background
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN) {
		if (x < 10) { x += 1; square_x += 16; }
	}
	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
		if (y > 0) { y -= 1; square_y -= 16; }
	}
	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
		if (x > 0) { x -= 1; square_x -= 16; }
	}
	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN) {
		if (y < 3) { y += 1; square_y += 16; }
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->scorescreen);
	}
	else if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN) {
		InputName();
	}

	App->render->Blit(App->ui->ui_graphics, square_x, square_y, &(square.GetCurrentFrame()));
	App->render->Blit(layout_graphic, 16, 88, &layout);

	return UPDATE_CONTINUE;
}

void ModuleNameScreen::InputName() {
	if (keyboard[x + 11 * y] == '<')
		App->ui->TopScores[rank].name[letter--] = ' ';
	else if (keyboard[x + 11 * y] == '/' || letter == 3) {
		App->fade->FadeToBlack(this, (Module*)App->title, 0.5f);
		letter = 0;
	}
	else {
		App->ui->TopScores[rank].name[letter] = keyboard[x + 11 * y];
		LOG("RANK: %d NAME LETTER: %d", rank, letter);
		letter++;
	}
	for (int i = 0; i < 5; i++) {
		LOG("INPUT %d %c%c%c %d %d", i, App->ui->TopScores[i].name[0], App->ui->TopScores[i].name[1], App->ui->TopScores[i].name[2], App->ui->TopScores[i].area, App->ui->TopScores[i].Tscore);
	}
}

void ModuleNameScreen::UpdateScores() {
	for (int i = 4; i > rank; i--) {
		for (int j = 0; j < 3; j++) {
			App->ui->TopScores[i].name[j] = App->ui->TopScores[i - 1].name[j];
		}
		App->ui->TopScores[i].area = App->ui->TopScores[i - 1].area;
		App->ui->TopScores[i].Tscore = App->ui->TopScores[i - 1].Tscore;
		LOG("UPDATING %d %c%c%c %d %d", i, App->ui->TopScores[i].name[0], App->ui->TopScores[i].name[1], App->ui->TopScores[i].name[2], App->ui->TopScores[i].area, App->ui->TopScores[i].Tscore);

	}
}