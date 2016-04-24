#include "Application.h"
#include "ModulePlayer.h"
#include "EnemyTruck.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"

#define nullrect {0,0,0,0} 

EnemyTruck::EnemyTruck(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type)
{
	original_pos = position;

	idle.PushBack({ 0, 65, 96, 126 });

	run.PushBack({ 96, 65, 96, 126 });
	run.PushBack({ 192, 65, 96, 126 });
	run.PushBack({ 288, 65, 96, 126 });
	run.PushBack({ 384, 65, 96, 126 });
	run.speed = 0.3f;
	run.loop = true;

	tex = App->particles->truck_footprint.tex;

	collider = App->collisions->AddCollider({ 0, 0, 70, 119 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	x_collider_correction = 10;
	y_collider_correction = -126;

	last_footprint = SDL_GetTicks();
	hp = 120;
	points = 1200;

	footprint = &App->particles->truck_footprint;

	dead_hole = &App->particles->truck_dead_hole;

	dead = &App->particles->truck_dead;

	mov.PushBack({ 0, 1.0f }, 114, &run);
	mov.PushBack({ 0, 0 }, 180, &idle);
	mov.PushBack({ 0, 1.0f }, 300, &run);

}

void EnemyTruck::UpdateAnim()
{
}

void EnemyTruck::Move(){
	
	now = SDL_GetTicks();

	if (hp>0){
		position = original_pos + mov.GetCurrentSpeed(&animation);
		if (now - last_footprint > 380){
				//App->particles->AddParticle(*footprint, position.x+14, position.y-24, footprint->collider, nullrect, 0);
				last_footprint = SDL_GetTicks();
		}
	}
	else{
		App->particles->AddParticle(*dead_hole, position.x, position.y-126, dead_hole->collider, nullrect, 0);
	}
}

void EnemyTruck::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x + x_collider_correction, position.y + y_collider_correction);

	App->render->Blit(tex, position.x, position.y-126, &(animation->GetCurrentFrame()));
}