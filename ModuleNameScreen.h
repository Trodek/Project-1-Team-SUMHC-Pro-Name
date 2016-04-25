#ifndef __MODULE_SCENE_NAME
#define __MODULE_SCENE_NAME

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleUI.h"
#include "ModuleAudio.h"

struct SDL_Texture;



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


public:

	char* keyboard;

	int x, y;
	int letter;
	int square_x;
	int square_y;
	int rank;
	Animation square;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* layout_graphic = nullptr;
	SDL_Rect layout;
	SDL_Rect name_screen;
	Mix_Music* music;

};

#endif // __MODULE_SCENE_NAME