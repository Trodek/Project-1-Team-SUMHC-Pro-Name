#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"



#define NUM_MODULES 17


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
<<<<<<< HEAD
class ModuleLevelsTop;
class ModuleSceneLevels;
=======
class ModuleLevel1;
class ModuleLevel2;
class ModuleLevel3;
>>>>>>> parent of c185ede... levels Wip



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
<<<<<<< HEAD
	ModuleLevelsTop* levelstop;
	ModuleSceneLevels* levels;
=======
	ModuleLevel3* level3;
>>>>>>> parent of c185ede... levels Wip
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