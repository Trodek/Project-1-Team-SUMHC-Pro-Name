#ifndef __MODULE_BOMB__
#define __MODULE_BOMB__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBomb : public Module
{
public:
	ModuleBomb();
	~ModuleBomb();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	bool pressed = false;
	SDL_Texture* bombtex = nullptr;
	Animation bombanim;
	Collider* BombCollider;
	bool collider_create = false;
};

#endif // __MODULE_BOMB__