#include "Application.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

class EnergyBox :public Enemy{
private:
	SDL_Rect image;
public:
	EnergyBox(int x, int y, ENEMY_TYPES types) : Enemy(x, y, types){
		position.x = x;
		position.y = y;

		tex = App->particles->boxes;
		
		image = { 24, 269, 40, 39 };

		collider = App->collisions->AddCollider({ 0, 0, 40, 39 }, COLLIDER_BOX, (Module*)App->enemies);
		collider->SetPos(position.x, position.y);

		hp = 1;
		points = 100;
	}

	void Draw(){
		App->render->Blit(tex, position.x, position.y, &image);
	}
};