#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

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
class ModuleLevel1;
class ModuleLevel2;
class ModuleLevel3;
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
	ModuleLevel3* level3;
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
	ModuleLevel1* level1;
	ModuleLevel2* level2;

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