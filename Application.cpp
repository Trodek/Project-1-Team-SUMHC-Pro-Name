#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneTitle.h"
#include "ModuleWinScreen.h"
#include "ModuleSceneLevels.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLoseScreen.h"
#include "ModuleNameScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleParticles.h"
#include "ModuleContinue.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = levels = new ModuleSceneLevels();
	modules[5] = title = new ModuleSceneTitle();
	modules[6] = player = new ModulePlayer();
	modules[7] = continuescreen = new ModuleContinue();
	modules[8] = audio = new ModuleAudio();
	modules[9] = winscreen = new ModuleWinScreen();
	modules[10] = losescreen = new ModuleLoseScreen();
	modules[11] = namescreen = new ModuleNameScreen();
	modules[12] = scorescreen = new ModuleScoreScreen();
	modules[13] = particles = new ModuleParticles();
	modules[14] = fade = new ModuleFadeToBlack(); // Fade Module must be the last of the scenes
	
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
	// Disable the map that you do not start with
	levels->Disable();
	winscreen->Disable();
	losescreen->Disable();
	namescreen->Disable();
	scorescreen->Disable();
	continuescreen->Disable();

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