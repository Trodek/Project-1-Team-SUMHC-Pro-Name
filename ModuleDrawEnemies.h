#ifndef _DrawEnemies_
#define _DrawEnemies_

#include "Globals.h"
#include "Application.h"
#include "Module.h"

class ModuleDrawEnemies :public Module{
public:
	update_status Update();
};

#endif