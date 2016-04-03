#ifndef __MODULE_SCENE_WINSCREEN
#define __MODULE_SCENE_WINSCREEN

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleWinScreen : public Module
{
public:
	ModuleWinScreen();
	~ModuleWinScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect win_screen;

};

#endif // __MODULE_SCENE_WINSCREEN