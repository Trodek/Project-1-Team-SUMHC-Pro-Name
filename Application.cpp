#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneTitle.h"
#include "ModuleWinScreen.h"
#include "ModuleSceneLevels.h"
#include "ModuleLevelsTop.h"
#include "ModulePlayer.h"
#include "ModuleGreenBasic.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLoseScreen.h"
#include "ModuleNameScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleParticles.h"
#include "ModuleContinue.h"
#include "ModuleCollision.h"
#include "ModuleBomb.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio(); // audio must be befor all the scenes
	modules[5] = title = new ModuleSceneTitle();
	modules[6] = continuescreen = new ModuleContinue();
	modules[7] = levels = new ModuleSceneLevels();
	modules[8] = winscreen = new ModuleWinScreen();
	modules[9] = losescreen = new ModuleLoseScreen();
	modules[10] = namescreen = new ModuleNameScreen();
	modules[11] = scorescreen = new ModuleScoreScreen();
	modules[12] = player = new ModulePlayer();
	modules[13] = green_basic_enemy = new ModuleGreenBasic();
	modules[14] = particles = new ModuleParticles();
	modules[15] = levelstop = new ModuleLevelsTop();
	modules[16] = collisions = new ModuleCollision;
	modules[17] = bomb = new ModuleBomb();
	modules[18] = fade = new ModuleFadeToBlack(); // Fade Module must be after the scenes
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	green_basic_enemy->Disable();
	// Disable the scenes that you do not start with
	levels->Disable();
	levelstop->Disable();
	winscreen->Disable();
	losescreen->Disable();
	namescreen->Disable();
	scorescreen->Disable();
	continuescreen->Disable();
	//Disable collision system
	collisions->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	//Stop audio 
	audio->StopAudio();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}