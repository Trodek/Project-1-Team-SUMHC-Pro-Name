#ifndef __MODULELEVEL2_H__
#define __MODULELEVEL2_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "dynArray.h"
#include "ModuleCollision.h"


struct SDL_Texture;

class ModuleLevel2 : public Module{
public:
	ModuleLevel2();
	~ModuleLevel2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	SDL_Rect map;

	Mix_Music* level2_song;

	dynArray<Collider*> colliders;

	bool change_music = true;

};

#endif