#include "Application.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "EnemyTrain.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "ModuleSceneLevels.h"

#define nullrect {0,0,0,0} 

EnemyTrain::EnemyTrain(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type)
{
	position.x = x;
	position.y = y;

	machine_top_anim.PushBack({ 232, 59, 115, 48 });
	door_anim.PushBack({ 0, 0, 116, 59 });
	door_anim.PushBack({ 116, 0, 116, 59 });
	door_anim.PushBack({ 232, 0, 116, 59 });
	door_anim.PushBack({ 0, 59, 116, 59 });
	door_anim.PushBack({ 116, 59, 116, 59 });
	door_anim.speed = 0.1f;
	turret_idle_anim.PushBack({ 6, 125, 24, 32 });
	turret_shot_anim.PushBack({ 53, 124, 24, 32 });
	turret_shot_anim.speed = 0.1f;

	tex = App->particles->train;

	last_enemy = SDL_GetTicks();

	dead = &App->particles->green_basic_dead;

	hp = 6;
	points = 390;
	collider = App->collisions->AddCollider({ 0, 0, 95, 83 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);
	bullet = &App->particles->big_turret_bullet;
	shoot_start = &App->particles->big_turret_bullet_start;
	draw = BEFORE;

}

void EnemyTrain::Move(){
	
	enemy_player_radius = position.DistanceTo(App->player->position);
	delta_y = position.y - App->player->position.y;
	delta_x = original.x - App->player->position.x;
	radius_deltax = enemy_player_radius - delta_x;

	if (hp > 0){
		position.x = App->levels->train_platform_pos_aux.x + 378;
	}
}

void EnemyTrain::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(tex, position.x, position.y + 48, &door_anim.GetCurrentFrame());
	App->render->Blit(tex, position.x, position.y, &machine_top_anim.GetCurrentFrame());
	if (shot_finish){
		App->render->Blit(tex, position.x + 7, position.y + 17, &turret_idle_anim.GetCurrentFrame());
	}
	else{
		App->render->Blit(tex, position.x + 7, position.y + 17, &turret_shot_anim.GetCurrentFrame());
	}
}

void EnemyTrain::Shot(){

	now = SDL_GetTicks();

	if (now - last_shot > 1000 && (position.y - App->player->position.y >-200 && position.y - App->player->position.y < 200
		&& position.x < SCREEN_WIDTH && position.x > 0)){
		shot_finish = false;
		float x_speed = (-delta_x / enemy_player_radius) * 3;
		float y_speed = (-delta_y / enemy_player_radius) * 3;
		App->particles->SetParticleSpeed(bullet, x_speed, y_speed);
		App->particles->AddParticle(*bullet, position.x + 10, position.y + 37, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
		App->particles->AddParticle(*shoot_start, position.x + 10, position.y + 37, COLLIDER_NONE, { 0, 0, 0, 0 });
		last_shot = SDL_GetTicks();
	}
	if (turret_shot_anim.Finished()){
		turret_shot_anim.Reset();
		shot_finish = true;
	}
}