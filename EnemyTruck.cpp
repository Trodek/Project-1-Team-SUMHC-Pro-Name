#include "Application.h"
#include "ModulePlayer.h"
#include "EnemyTruck.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL_timer.h"

#define nullrect {0,0,0,0} 

EnemyTruck::EnemyTruck(int x, int y) : Enemy(x, y)
{
	run.PushBack({ 13, 39, 80, 124 });
	run.PushBack({ 107, 39, 80, 123 });
	run.PushBack({ 206, 39, 80, 124 });
	run.PushBack({ 305, 39, 80, 125 });
	run.speed = 0.3f;
	run.loop = true;

	tex = App->particles->truck_footprint.tex;

	collider = App->collisions->AddCollider({ 0, 0, 70, 110 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &run;
	last_footprint = SDL_GetTicks();
	hp = 120;
	points = 1200;

	footprint = &App->particles->truck_footprint;

	dead = &App->particles->big_turret_dead; //truck destroy anim not yet made

}

void EnemyTruck::UpdateAnim()
{
}

void EnemyTruck::Move(){

	now = SDL_GetTicks();
	int speed = 1;

	position.y += speed;

	if (hp>0){
		if (now - last_footprint > 380){
				App->particles->AddParticle(*footprint, position.x+1, position.y-22, footprint->collider, nullrect, 0);
				last_footprint = SDL_GetTicks();
		}
	}
}