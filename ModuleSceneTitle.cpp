#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneTitle.h"
#include "ModulePlayer.h"
#include "ModuleGreenBasic.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleSceneLevels.h"
#include "ModuleUI.h"


ModuleSceneTitle::ModuleSceneTitle()
{
	// ground
	title_screen.x = 0;
	title_screen.y = 0;
	title_screen.w = 240;
	title_screen.h = 320;

}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading Title scene");
	
	graphics = App->textures->Load("OutZone/Sprites/UI/ui_maintitle.png");
	App->player->Disable();
	App->green_basic_enemy->Disable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading Title scene");
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneTitle::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &title_screen, 0.75f); // background
	
	// swap Scene
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->levels, 1.0f);
		App->ui->SubCoin();
	}
	


	return UPDATE_CONTINUE;
}