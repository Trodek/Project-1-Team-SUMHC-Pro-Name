#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneTitle.h"
#include "ModuleWinScreen.h"
#include "ModuleSceneLevels.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLoseScreen.h"
#include "ModuleNameScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleParticles.h"
#include "ModuleContinue.h"
#include "ModuleCollision.h"

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
	modules[8] = level1 = new ModuleLevel1();
	modules[9] = level2 = new ModuleLevel2();
	modules[10] = winscreen = new ModuleWinScreen();
	modules[11] = losescreen = new ModuleLoseScreen();
	modules[12] = namescreen = new ModuleNameScreen();
	modules[13] = scorescreen = new ModuleScoreScreen();
	modules[14] = player = new ModulePlayer();
	modules[15] = particles = new ModuleParticles();
	modules[16] = collisions = new ModuleCollision;
	modules[17] = fade = new ModuleFadeToBlack(); // Fade Module must be after the scenes
	
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
	// Disable the scenes that you do not start with
	levels->Disable();
	level1->Disable();
	level2->Disable();
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