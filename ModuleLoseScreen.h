#ifndef __MODULE_SCENE_LOSE
#define __MODULE_SCENE_LOSE

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"

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

	Mix_Music* gameover_song;
	uint born;
	uint now;

};

#endif // __MODULE_SCENE_LOSE