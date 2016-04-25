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

	//TopScores
	TopScores.PushBack({ "   ", 0, 200000 });
	TopScores.PushBack({ "   ", 0, 100000 });
	TopScores.PushBack({ "   ", 0, 50000 });
	TopScores.PushBack({ "   ", 0, 20000 });
	TopScores.PushBack({ "   ", 0, 10000 });


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
	for (int i = 0; i < 5; i++) {
		if (TopScores[i].Tscore < App->ui->score) {
			rank = i;
			break;
		}
	}
	App->audio->PlayMusic(music,LOOP);
	//Square Position
	square_x = 28;
	square_y = 165;

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
	//delete[] keyboard;
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
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->title, 0.5f);
	}
	/*else if (App->input->keyboard[SDL_SCANCODE_F] == 1) {
		InputName();
	}*/	

	App->render->Blit(App->ui->ui_graphics, square_x, square_y, &(square.GetCurrentFrame()));
	App->render->Blit(layout_graphic, 16, 88, &layout);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		App->fade->FadeToBlack(this, (Module*)App->scorescreen);
	}



	return UPDATE_CONTINUE;
}

void ModuleNameScreen::InputName() {
	if (keyboard[x + x*y] == '<')
		TopScores[rank].name[letter--] = ' ';
	else if (keyboard[x + x*y] == '/')
		App->fade->FadeToBlack(this, (Module*)App->title, 0.5f);
	else
		TopScores[rank].name[letter] = keyboard[x + x*y];
	LOG("%c", TopScores[rank].name[letter])
}

bool TopScore() {
	return false;
}

void ModuleNameScreen::UpdateScores() {
	for (int i = 4; i > rank; i++) {
		TopScores[i].name = TopScores[i - 1].name;
		TopScores[i].area = TopScores[i - 1].area;
		TopScores[i].Tscore = TopScores[i - 1].Tscore;
	}
}