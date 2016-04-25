#ifndef __MODULE_SCENE_SCORE
#define __MODULE_SCENE_SCORE

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;


class ModuleScoreScreen : public Module
{
public:
	ModuleScoreScreen();
	~ModuleScoreScreen();

	bool Start();
	update_status Update();
	bool CleanUp();



public:

	SDL_Rect position;
	SDL_Rect name;
	SDL_Rect score;

	int x, y;
	int aux;
	int temp_score;
	char* keyboard;
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect score_screen;

};

#endif // __MODULE_SCENE_SCORE