#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"


#define NUM_MODULES 22


class ModuleWindow;
class ModuleInput;
class ModuleParticles;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTitle;
class ModuleWinScreen;
class ModulePlayer;
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
class ModuleGreenBasic;
class ModuleBomb;
class ModuleBigTurret;
class ModuleTruck;
class ModuleUI;



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
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleLoseScreen* losescreen;
	ModuleNameScreen* namescreen;
	ModuleScoreScreen* scorescreen;
	ModuleContinue* continuescreen;
	ModuleParticles* particles;
	ModuleCollision* collisions;
	ModuleGreenBasic* green_basic_enemy;
	ModuleBomb* bomb;
	ModuleBigTurret* enemy_big_turret;
	ModuleTruck* enemy_truck;
	ModuleUI* ui;


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