#ifndef __MODULECONTINUE_H__
#define __MODULECONTINUE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

class ModuleContinue : public Module
{
public:
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect continue_screen;

	Mix_Music* continue_song;
	uint born;
	uint now;

};

#endif 