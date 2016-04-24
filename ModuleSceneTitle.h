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
	int starttime;
public:
	
	SDL_Texture* title_tex = nullptr;
	SDL_Rect title_screen;
	Animation title_anim;


	
	SDL_Texture* chars_tex = nullptr;
	//Char o
	int ox, oy;
	SDL_Rect chars_rec_o;
	//

};

#endif // __MODULESCENETitle_H__