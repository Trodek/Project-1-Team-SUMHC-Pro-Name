#ifndef __EXTRA_BOMB_H__
#define __EXTRA_BOMB_H__

#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "Enemy.h"

class Extra_Bomb :public Enemy{
private:
	Animation anim;

public:
	Extra_Bomb(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
		position.x = x;
		position.y = y;

		tex = App->particles->boxes;

		collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, COLLIDER_EXTRA_BOMB, (Module*)App->enemies);
		collider->SetPos(position.x, position.y);

		anim.PushBack({ 16, 183, 16, 16 });
		anim.PushBack({ 39, 183, 16, 16 });
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