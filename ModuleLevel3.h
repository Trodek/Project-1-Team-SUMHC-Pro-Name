#ifndef __MODULELEVEL3_H__
#define __MODULELEVEL3_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "dynArray.h"
#include "ModuleCollision.h"


struct SDL_Texture;

class ModuleLevel3 : public Module{
public:
	ModuleLevel3();
	~ModuleLevel3();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	SDL_Rect map;

	Mix_Music* level3_song;

	dynArray<Collider*> colliders;

};

#endif