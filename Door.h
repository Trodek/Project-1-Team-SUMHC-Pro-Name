#ifndef __DOOR_H__
#define __DOOR_H__

#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "Enemy.h"

class Door : public Enemy{
private:
	SDL_Rect text_rect;

public:
	Door(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
		position.x = x;
		position.y = y;

		tex = App->textures->Load("OutZone/Sprites/Enemies/Level 4/door.png");
		

		collider = App->collisions->AddCollider({ 0, 0, 121, 90 }, COLLIDER_DOOR, (Module*)App->enemies);
		collider->SetPos(position.x, position.y);

		text_rect.x = 0;
		text_rect.y = 0;
		text_rect.w = 121;
		text_rect.h = 113;

		hp = 240;
		points = 500;

		draw = BEFORE;

	}

	void Draw(){
		App->render->Blit(tex, position.x, position.y, &text_rect);
	}
};

#endif