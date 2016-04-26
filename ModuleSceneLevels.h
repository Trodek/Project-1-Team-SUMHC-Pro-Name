#ifndef __MODULESCENELEVELS_H__
#define __MODULESCENELEVELS_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "Path.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

class ModuleSceneLevels : public Module
{
public:
	ModuleSceneLevels();
	~ModuleSceneLevels();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool CameraReset();
	void RestartEnemiesPaths();

public:

	SDL_Texture* graphics_l1 = nullptr;
	SDL_Texture* graphics_l2 = nullptr;
	SDL_Texture* graphics_l3 = nullptr;
	SDL_Texture* lava = nullptr;
	SDL_Texture* on_bg = nullptr;
	SDL_Texture* sublighttex = nullptr;

	Animation lavaanim;
	Animation sublightanim;
	Animation lights;
	SDL_Rect level1;
	SDL_Rect level2;
	SDL_Rect level3;
	float camera_y;

	Mix_Music* level1_song;
	Mix_Music* level2_song;
	Mix_Music* level3_song;

	Path gb1;
	Path gb2;
	Path gb3;
	Path gb4;
	Path gb5;
	Path gb6;
	Path gb7;
	Path gb8;
	Path gb9;
	Path gb10;
	Path gb11;
	Path gb12;
	Path gb13;
	Path gb14;
	Path gb15;
	Path gb16;
	Path gb17;
	Path gb18;
	Path gb19;
	Path gb20;


};

#endif // __MODULESCENELevels_H__