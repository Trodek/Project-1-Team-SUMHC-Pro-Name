#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:
	iPoint position;
	SDL_Texture* main_char_tex = nullptr;
	Animation up;
	Animation idle_up;
	Animation down;
	Animation idle_down;
	Animation up_to_left;
	Animation left;
	Animation idle_left;
	Animation up_to_right;
	Animation right;
	Animation idle_right;
	Animation* current_animation = nullptr;
	Animation char_move_360;
};

#endif