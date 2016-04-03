#ifndef __MODULE_SCENE_NAME
#define __MODULE_SCENE_NAME

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleNameScreen : public Module
{
public:
	ModuleNameScreen();
	~ModuleNameScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect name_screen;

};

#endif // __MODULE_SCENE_NAME