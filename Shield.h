#ifndef __SPEED_H__
#define __SPEED_H__

#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "Enemy.h"

class Shield :public Enemy{
private:
	Animation anim;

public:
	Shield(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
		position.x = x;
		position.y = y;

		tex = App->particles->boxes;

		collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, COLLIDER_SHIELD, (Module*)App->enemies);
		collider->SetPos(position.x, position.y);

		anim.PushBack({ 79, 34, 24, 24 });
		anim.PushBack({ 115, 34, 24, 24 });
		anim.speed = 0.2f;

		hp = 1;
		points = 50;

		draw = PILL;

	}

	void Draw(){
		App->render->Blit(tex, position.x, position.y, &anim.GetCurrentFrame());
	}
};


#endif