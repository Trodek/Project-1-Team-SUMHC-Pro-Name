#ifndef __MODULESCENELEVELS_H__
#define __MODULESCENELEVELS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
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

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* lava = nullptr;
	SDL_Texture* on_bg = nullptr;
	Animation lavaanim;
	Animation lights;
	SDL_Rect map;
	
	int camera_y;

	Mix_Music* level1_song;
	Mix_Music* level2_song;
	Mix_Music* level3_song;

};

#endif // __MODULESCENELevels_H__