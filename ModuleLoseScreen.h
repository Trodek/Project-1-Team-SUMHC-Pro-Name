#ifndef __MODULE_SCENE_LOSE
#define __MODULE_SCENE_LOSE

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLoseScreen : public Module
{
public:
	ModuleLoseScreen();
	~ModuleLoseScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect lose_screen;

};

#endif // __MODULE_SCENE_LOSE