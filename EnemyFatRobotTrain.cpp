#include "Application.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "EnemyFatRobotTrain.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "ModuleSceneLevels.h"

EnemyFatRobotTrain::EnemyFatRobotTrain(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type){

	original = position;

	idle.PushBack({ 0, 0, 63, 72 });

	tex = App->particles->fat_robot_train;

	last_shot = SDL_GetTicks();

	dead = &App->particles->green_basic_dead;

	hp = 114;
	points = 800;
	collider = App->collisions->AddCollider({ 0, 0, 63, 72 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);
	bullet = &App->particles->green_basic_bullet;
	shoot_start = &App->particles->green_basic_bullet_start;
	draw = BEFORE;
}

void EnemyFatRobotTrain::Move(){

	original.x = App->levels->train_platform_pos_aux.x + position.x;

}

void EnemyFatRobotTrain::Draw(){

	if (collider != nullptr)
		collider->SetPos(original.x, position.y);

	App->render->Blit(tex, original.x, position.y, &idle.GetActualFrame());
}

void EnemyFatRobotTrain::Shot(){

	now = SDL_GetTicks();

	if (now - last_shot > 3000 && (position.y - App->player->position.y >-200 && position.y - App->player->position.y < 200
		&& original.x < SCREEN_WIDTH && original.x > 0)){
		App->particles->SetParticleSpeed(bullet, 0, 2);
		App->particles->AddParticle(*bullet, original.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
		App->particles->AddParticle(*shoot_start, original.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
		
		last_shot = SDL_GetTicks();
	}
}