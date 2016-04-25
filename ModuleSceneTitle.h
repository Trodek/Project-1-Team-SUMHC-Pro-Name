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
	//Char U
	int ux, uy;
	SDL_Rect chars_rec_u;
	//
	//Char T
	int tx, ty;
	SDL_Rect chars_rec_t;
	//
	//Char Z
	int zx, zy;
	SDL_Rect chars_rec_z;
	//
	//Char o2
	int o2x, o2y;
	SDL_Rect chars_rec_o2;
	//
	//Char n
	int nx, ny;
	SDL_Rect chars_rec_n;
	//
	//Char e
	int ex, ey;
	SDL_Rect chars_rec_e;
	//
	//THIS WILL BE THE BRIGHT ONES
	//Char ob
	int obx, oby;
	SDL_Rect chars_rec_ob;
	//
	//Char Ub
	int ubx, uby;
	SDL_Rect chars_rec_ub;
	//
	//Char Tb
	int tbx, tby;
	SDL_Rect chars_rec_tb;
	//
	//Char Zb
	int zbx, zby;
	SDL_Rect chars_rec_zb;
	//
	//Char o2b
	int o2bx, o2by;
	SDL_Rect chars_rec_o2b;
	//
	//Char nb
	int nbx, nby;
	SDL_Rect chars_rec_nb;
	//
	//Char eb
	int ebx, eby;
	SDL_Rect chars_rec_eb;
	//


};

#endif // __MODULESCENETitle_H__