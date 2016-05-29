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
	void RestartEnemies();
	void AddEnergyBox(int x, int y);
	void AddChangeBox(int x, int y);

public:

	SDL_Texture* graphics_l4 = nullptr;
	SDL_Texture* graphics_l4_below = nullptr;
	SDL_Texture* lava = nullptr;
	SDL_Texture* on_bg = nullptr;
	SDL_Texture* sublighttex = nullptr;

	Animation lavaanim;
	Animation sublightanim;
	Animation lights;

	SDL_Rect level4;


	float camera_y;

	Mix_Music* level4_song;

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
	Path gb21;
	Path roomba1;
	Path roomba2;
	Path roomba3;
	Path notsobasic1;
	Path notsobasic2;
	Path notsobasic3;
	Path fastright;
	Path fastright1;
	Path fastright2;
	Path fastright3;
	Path sl1;
	Path sl2;
	Path sl3;
	Path sl4;
	Path sl5;
	Path sl6;

	//Platform stuff
	Path platform_p;
	Animation platform_anim;
	SDL_Texture* platform_t = nullptr;
	iPoint platform1_pos;
	iPoint platform1_aux_pos;
	Collider* platform_1_1;
	Collider* platform_1_2;
	iPoint platform2_pos;
	iPoint platform2_aux_pos;
	Collider* platform_2_1;
	Collider* platform_2_2;
	iPoint platform3_pos;
	iPoint platform3_aux_pos;
	Collider* platform_3_1;
	Collider* platform_3_2;
};

#endif // __MODULESCENELevels_H__