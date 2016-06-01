#include "Application.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "EnemyBlueBasic.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "ModuleSceneLevels.h"

EnemyBlueBasic::EnemyBlueBasic(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type){

	position.x = x;
	position.y = y;
	original = position;
	dir = IDLE;

	//move 360º
	move_360.PushBack({ 0, 0, 32, 37 });  //-- left
	move_360.PushBack({ 224, 37, 32, 37 }); //-- left-up
	move_360.PushBack({ 192, 37, 32, 37 }); //-- left-up
	move_360.PushBack({ 160, 37, 32, 37 }); //-- left-up
	move_360.PushBack({ 128, 37, 32, 37 });  //-- up
	move_360.PushBack({ 96, 37, 32, 37 });  //-- right-up
	move_360.PushBack({ 64, 37, 32, 37 });  //-- right-up
	move_360.PushBack({ 32, 37, 32, 37 });  //-- right-up
	move_360.PushBack({ 0, 37, 32, 37 });  //-- right
	move_360.PushBack({ 224, 0, 32, 37 });  //-- right-down
	move_360.PushBack({ 192, 0, 32, 37 });  //-- right-down
	move_360.PushBack({ 160, 0, 32, 37 });  //-- right-down
	move_360.PushBack({ 128, 0, 32, 37 });  //-- down
	move_360.PushBack({ 96, 0, 32, 37 });  //-- left-down
	move_360.PushBack({ 64, 0, 32, 37 });  //-- left-down
	move_360.PushBack({ 32, 0, 32, 37 });  //-- left-down
	move_360.speed = 0.6f;
	move_360.SetInitialFrame(DOWN);

	tex = App->particles->blue_basic;

	last_shot = SDL_GetTicks();

	dead = &App->particles->green_basic_dead;

	hp = 6;
	points = 390;
	collider = App->collisions->AddCollider({ 0, 0, 23, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);
	bullet = &App->particles->green_basic_bullet;
	shoot_start = &App->particles->green_basic_bullet_start;
	draw = BEFORE;
}

void EnemyBlueBasic::Move(){

	//-----------Face Player---------------

	enemy_player_radius = position.DistanceTo(App->player->position);
	delta_y = position.y - App->player->position.y;
	delta_x = original.x - App->player->position.x;
	radius_deltax = enemy_player_radius - delta_x;

	if (radius_deltax < enemy_player_radius / 5){
		move_360.SetInitialFrame(LEFT);
		dir = LEFT;
	}
	else if (radius_deltax > 4 * enemy_player_radius / 5 && radius_deltax <= 6 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(UP);
			dir = UP;
		}
		else {
			move_360.SetInitialFrame(DOWN);
			dir = DOWN;
		}
	}
	else if (radius_deltax > enemy_player_radius / 5 && radius_deltax < 2 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_60);
			dir = ANGLE_60;
		}
		else {
			move_360.SetInitialFrame(ANGLE_120);
			dir = ANGLE_120;
		}
	}
	else if (radius_deltax > 2 * enemy_player_radius / 5 && radius_deltax < 3 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(LEFT_UP);
			dir = LEFT_UP;
		}
		else {
			move_360.SetInitialFrame(LEFT_DOWN);
			dir = LEFT_DOWN;
		}
	}
	else if (radius_deltax > 3 * enemy_player_radius / 5 && radius_deltax < 4 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_30);
			dir = ANGLE_30;
		}
		else {
			move_360.SetInitialFrame(ANGLE_150);
			dir = ANGLE_150;
		}
	}
	else if (radius_deltax > 6 * enemy_player_radius / 5 && radius_deltax < 7 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_330);
			dir = ANGLE_330;
		}
		else {
			move_360.SetInitialFrame(ANGLE_210);
			dir = ANGLE_210;
		}
	}
	else if (radius_deltax > 7 * enemy_player_radius / 5 && radius_deltax < 8 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(RIGHT_UP);
			dir = RIGHT_UP;
		}
		else {
			move_360.SetInitialFrame(RIGHT_DOWN);
			dir = RIGHT_DOWN;
		}
	}
	else if (radius_deltax > 8 * enemy_player_radius / 5 && radius_deltax < 9 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_300);
			dir = ANGLE_300;
		}
		else {
			move_360.SetInitialFrame(ANGLE_240);
			dir = ANGLE_240;
		}
	}
	else if (radius_deltax > 9 * enemy_player_radius / 5 && radius_deltax < 2 * enemy_player_radius){
		move_360.SetInitialFrame(RIGHT);
		dir = RIGHT;
	}

	//-----------------------------------------------
	
	original.x = App->levels->train_platform_pos_aux.x + position.x;
}

void EnemyBlueBasic::Draw(){

	if (collider != nullptr)
		collider->SetPos(original.x, position.y);

	App->render->Blit(tex, original.x, position.y, &move_360.GetActualFrame());
}

void EnemyBlueBasic::Shot(){

	now = SDL_GetTicks();

	if (now - last_shot > 3000 && (position.y - App->player->position.y >-200 && position.y - App->player->position.y < 200
		&& original.x < SCREEN_WIDTH - 20 && original.x > 20)){
		float x_speed = (-delta_x / enemy_player_radius) * 3;
		float y_speed = (-delta_y / enemy_player_radius) * 3;
		App->particles->SetParticleSpeed(bullet, x_speed, y_speed);
		switch (dir)
		{
		case LEFT:
			App->particles->AddParticle(*bullet, original.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_60:
			App->particles->AddParticle(*bullet, original.x, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x - 8, position.y, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_UP:
			App->particles->AddParticle(*bullet, original.x + 5, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x - 3, position.y - 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_30:
			App->particles->AddParticle(*bullet, original.x + 8, position.y - 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 1, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case UP:
			App->particles->AddParticle(*bullet, original.x + 10, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 5, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_330:
			App->particles->AddParticle(*bullet, original.x + 19, position.y - 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 12, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_UP:
			App->particles->AddParticle(*bullet, original.x + 27, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 19, position.y - 4, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_300:
			App->particles->AddParticle(*bullet, original.x + 22, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 16, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT:
			App->particles->AddParticle(*bullet, original.x + 25, position.y + 13, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 22, position.y + 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_240:
			App->particles->AddParticle(*bullet, original.x + 21, position.y + 13, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 18, position.y + 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_DOWN:
			App->particles->AddParticle(*bullet, original.x + 24, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 16, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_210:
			App->particles->AddParticle(*bullet, original.x + 20, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 12, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case DOWN:
			App->particles->AddParticle(*bullet, original.x + 10, position.y + 25, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x + 5, position.y + 20, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_150:
			App->particles->AddParticle(*bullet, original.x + 5, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x - 3, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_DOWN:
			App->particles->AddParticle(*bullet, original.x + 3, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x - 5, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_120:
			App->particles->AddParticle(*bullet, original.x + 3, position.y + 15, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, original.x - 5, position.y + 10, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		}
		last_shot = SDL_GetTicks();
	}
}