#ifndef __MODULESCENETITLE_H__
#define __MODULESCENETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneTitle : public Module
{
public:
	ModuleSceneTitle();
	~ModuleSceneTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* title_tex = nullptr;
	SDL_Rect title_screen;

	Animation title_anim;
	
};

#endif // __MODULESCENETitle_H__