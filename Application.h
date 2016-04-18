#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

<<<<<<< HEAD
#define NUM_MODULES 19
=======
#define NUM_MODULES 17
>>>>>>> origin/master

class ModuleWindow;
class ModuleInput;
class ModuleParticles;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTitle;
class ModuleWinScreen;
class ModulePlayer;
class ModuleGreenBasic;
class ModuleFadeToBlack;
class ModuleAudio;
class ModuleLoseScreen;
class ModuleScoreScreen;
class ModuleNameScreen;
class ModuleContinue;
class ModuleCollision;
class Module;
class ModuleLevelsTop;
class ModuleSceneLevels;



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
	ModuleLevelsTop* levelstop;
	ModuleSceneLevels* levels;
	ModulePlayer* player;
	ModuleGreenBasic* basic_green_enemy;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleLoseScreen* losescreen;
	ModuleNameScreen* namescreen;
	ModuleScoreScreen* scorescreen;
	ModuleContinue* continuescreen;
	ModuleParticles* particles;
	ModuleCollision* collisions;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	Module* current_level=nullptr;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__