#include "Application.h"
#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleDrawEnemies.h"

update_status ModuleDrawEnemies::Update(){
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (App->enemies->enemies[i] != nullptr && App->enemies->enemies[i]->draw == PILL) App->enemies->enemies[i]->Draw();
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	if (App->enemies->enemies[i] != nullptr && App->enemies->enemies[i]->draw == BEFORE) App->enemies->enemies[i]->Draw();

	return UPDATE_CONTINUE;
}