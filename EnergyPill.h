#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "Enemy.h"

class EnergyPill :public Enemy{
private:
	Animation anim;

public:
	EnergyPill(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
		position.x = x;
		position.y = y;

		tex = App->particles->boxes;

		collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, COLLIDER_ENERGY, (Module*)App->enemies);
		collider->SetPos(position.x, position.y);

		anim.PushBack({ 16, 183, 16, 16 });
		anim.PushBack({ 39, 183, 16, 16 });
		anim.speed = 0.4f;
		
	}

	void Draw(){
		App->render->Blit(tex, position.x, position.y, &anim.GetCurrentFrame());
	}
};