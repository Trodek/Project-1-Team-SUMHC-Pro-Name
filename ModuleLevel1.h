#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "dynArray.h"
#include "ModuleCollision.h"


struct SDL_Texture;

class ModuleLevel1 : public Module{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	SDL_Rect map;

	Mix_Music* level1_song;

	dynArray<Collider*> colliders;

};


#endif