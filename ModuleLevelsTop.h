#ifndef _ModuleLevelsTop_
#define _ModuleLevelsTop_

#include "ModuleTextures.h"
#include "Globals.h"
#include "Module.h"

class ModuleLevelsTop : public Module
{
public:
	ModuleLevelsTop();
	~ModuleLevelsTop();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* level1_top;
	SDL_Texture* level2_top;
	SDL_Texture* level3_top;

	SDL_Rect level1;
	SDL_Rect level2;
	SDL_Rect level3;

};



#endif