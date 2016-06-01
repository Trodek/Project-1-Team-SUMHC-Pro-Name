#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "Enemy.h"

class PowerUP :public Enemy{
private:
	Animation anim;

public:
	PowerUP(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
		position.x = x;
		position.y = y;

		tex = App->particles->boxes;

		collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, COLLIDER_POWERUP, (Module*)App->enemies);
		collider->SetPos(position.x, position.y);

		anim.PushBack({ 16, 129, 16, 16 });
		anim.PushBack({ 39, 129, 16, 16 });
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