#ifndef __MODULESCENETITLE_H__
#define __MODULESCENETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"
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
	
	bool no_pay = true;

	SDL_Texture* title_tex = nullptr;
	SDL_Rect title_screen;
	Animation title_anim;

	SDL_Texture* player_blue = nullptr;
	SDL_Rect player_blue_rec;
	SDL_Texture* copyr = nullptr;
	SDL_Rect copyr_rec;

	SDL_Texture* chars_tex = nullptr;

	SDL_Rect chars_rec_e;
	Animation e_anim;
	//O
	Path Ob_path;
	Animation Ob_anim;
	iPoint o;
	iPoint co;
	//u
	Path ub_path;
	Animation ub_anim;
	iPoint u;
	iPoint cu;
	//T
	Path tb_path;
	Animation tb_anim;
	iPoint t;
	iPoint ct;
	//Z
	Path zb_path;
	Animation zb_anim;
	iPoint z;
	iPoint cz;
	//O2
	Path o2b_path;
	Animation o2b_anim;
	iPoint o2;
	iPoint co2;
	//n
	Path nb_path;
	Animation nb_anim;
	iPoint n;
	iPoint cn;
	//e
	Path eb_path;
	Animation eb_anim;
	iPoint e;
	iPoint ce;


};

#endif // __MODULESCENETitle_H__