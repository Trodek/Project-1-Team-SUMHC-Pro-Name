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

	SDL_Texture* level4_top;

	SDL_Rect level4;


};



#endif