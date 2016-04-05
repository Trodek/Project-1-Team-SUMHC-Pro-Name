#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 15

class ModuleWindow;
class ModuleInput;
class ModuleParticles;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTitle;
class ModuleSceneLevels;
class ModuleWinScreen;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleAudio;
class ModuleLoseScreen;
class ModuleScoreScreen;
class ModuleNameScreen;
class ModuleContinue;
class Module;



class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleWinScreen* winscreen;
	ModuleTextures* textures;
	ModuleSceneTitle* title;
	ModuleSceneLevels* levels;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleLoseScreen* losescreen;
	ModuleNameScreen* namescreen;
	ModuleScoreScreen* scorescreen;
	ModuleContinue* continuescreen;
	ModuleParticles* particles;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__