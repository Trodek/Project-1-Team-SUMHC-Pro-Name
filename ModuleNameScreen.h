#ifndef __MODULE_SCENE_NAME
#define __MODULE_SCENE_NAME

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "dynArray.h"
#include "ModuleUI.h"

struct SDL_Texture;

struct Ranking {
	char* name;
	int area, Tscore;
};

class ModuleNameScreen : public Module
{
public:
	ModuleNameScreen();
	~ModuleNameScreen();

	bool Start();
	update_status Update();
	bool CleanUp();
	void UpdateScores();
	void InputName();
	bool TopScore();

public:

	char* keyboard;
	int x = 0, y = 0;
	int letter = 0;
	int square_x;
	int square_y;
	int rank;
	Animation square;
	dynArray<Ranking> TopScores;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* layout_graphic = nullptr;
	SDL_Rect layout;
	SDL_Rect name_screen;

};

#endif // __MODULE_SCENE_NAME