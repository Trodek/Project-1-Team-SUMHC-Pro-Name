#include "Application.h"
#include "ModulePlayer.h"
#include "EnemyTrain.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"

#define nullrect {0,0,0,0} 

EnemyTrain::EnemyTrain(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type)
{
	original_pos = position;

	idle.PushBack({ 0, 65, 96, 126 });

	tex = App->particles->truck_footprint.tex;

	collider = App->collisions->AddCollider({ 0, 0, 70, 119 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	x_collider_correction = 10;
	y_collider_correction = -126;

	hp = 120;
	points = 1200;

	dead_hole = &App->particles->truck_dead_hole;

	dead = &App->particles->truck_dead;

	mov.PushBack({ 0, 0 }, 180, &idle);

}

void EnemyTrain::UpdateAnim()
{
}

void EnemyTrain::Move(){
	
	now = SDL_GetTicks();

	if (hp>0){
		position = original_pos + mov.GetCurrentSpeed(&animation);
	}
}

void EnemyTrain::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x + x_collider_correction, position.y + y_collider_correction);

	App->render->Blit(tex, position.x, position.y-126, &(animation->GetCurrentFrame()));
}