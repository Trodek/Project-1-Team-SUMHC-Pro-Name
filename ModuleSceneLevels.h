#ifndef __MODULESCENELEVELS_H__
#define __MODULESCENELEVELS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneLevels : public Module
{
public:
	ModuleSceneLevels();
	~ModuleSceneLevels();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool CameraReset();
public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect map;
	int camera_y;

};

#endif // __MODULESCENELevels_H__