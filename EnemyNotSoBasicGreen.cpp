#include "Application.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "EnemyNotSoBasicGreen.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"

EnemyNotSoBasicGreen::EnemyNotSoBasicGreen(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type){

	original = position;

	dir = IDLE;

	//Char Up anim
	up.PushBack({ 171, 147, 23, 32 });
	up.PushBack({ 204, 147, 24, 31 });
	up.PushBack({ 237, 147, 23, 32 });
	up.PushBack({ 271, 147, 25, 32 });
	up.speed = 0.05f;

	//char right
	right.PushBack({ 23, 63, 24, 31 });
	right.PushBack({ 55, 62, 24, 32 });
	right.PushBack({ 87, 64, 29, 31 });
	right.PushBack({ 122, 64, 26, 32 });
	right.speed = 0.07f;

	//char left
	left.PushBack({ 273, 63, 29, 31 });
	left.PushBack({ 234, 63, 26, 32 });
	left.PushBack({ 200, 64, 28, 31 });
	left.PushBack({ 165, 63, 27, 32 });
	left.speed = 0.07f;

	//char down
	down.PushBack({ 19, 148, 23, 31 });
	down.PushBack({ 51, 147, 22, 32 });
	down.PushBack({ 84, 148, 23, 31 });
	down.PushBack({ 118, 147, 23, 32 });
	down.speed = 0.07f;

	//char left-up
	left_up.PushBack({ 166, 21, 25, 31 });
	left_up.PushBack({ 205, 21, 21, 32 });
	left_up.PushBack({ 242, 21, 24, 31 });
	left_up.PushBack({ 275, 20, 25, 32 });
	left_up.speed = 0.05f;

	// char left-down
	left_down.PushBack({ 165, 105, 27, 32 });
	left_down.PushBack({ 200, 106, 29, 31 });
	left_down.PushBack({ 237, 106, 28, 32 });
	left_down.PushBack({ 273, 107, 29, 31 });
	left_down.speed = 0.05f;

	// char right-down
	right_down.PushBack({ 19, 103, 23, 32 });
	right_down.PushBack({ 50, 104, 23, 31 });
	right_down.PushBack({ 81, 104, 24, 32 });
	right_down.PushBack({ 118, 105, 23, 31 });
	right_down.speed = 0.05f;

	// char right-up
	right_up.PushBack({ 19, 20, 29, 30 });
	right_up.PushBack({ 55, 21, 26, 31 });
	right_up.PushBack({ 92, 22, 24, 30 });
	right_up.PushBack({ 123, 21, 27, 31 });
	right_up.speed = 0.05f;

	//move 360º
	move_360.PushBack({ 273, 63, 29, 31 });  //-- left
	move_360.PushBack({ 166, 21, 25, 31 }); //-- left-up
	move_360.PushBack({ 166, 21, 25, 31 }); //-- left-up
	move_360.PushBack({ 166, 21, 25, 31 }); //-- left-up
	move_360.PushBack({ 171, 147, 23, 32 });  //-- up
	move_360.PushBack({ 19, 20, 29, 30 });  //-- right-up
	move_360.PushBack({ 19, 20, 29, 30 });  //-- right-up
	move_360.PushBack({ 19, 20, 29, 30 });  //-- right-up
	move_360.PushBack({ 23, 63, 24, 31 }); //-- right
	move_360.PushBack({ 19, 103, 23, 32 });  //-- right-down
	move_360.PushBack({ 19, 103, 23, 32 });  //-- right-down
	move_360.PushBack({ 19, 103, 23, 32 });  //-- right-down
	move_360.PushBack({ 19, 148, 23, 31 });  //-- down
	move_360.PushBack({ 165, 105, 27, 32 });  //-- left-down
	move_360.PushBack({ 165, 105, 27, 32 });  //-- left-down
	move_360.PushBack({ 165, 105, 27, 32 });  //-- left-down
	move_360.speed = 0.6f;
	move_360.SetInitialFrame(DOWN);

	tex = App->particles->notsobasicgreen;

	last_shot = SDL_GetTicks();

	dead = &App->particles->green_basic_dead;

	hp = 6;
	points = 390;
	collider = App->collisions->AddCollider({ 0, 0, 23, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);
	bullet = &App->particles->green_basic_bullet;
	shoot_start = &App->particles->green_basic_bullet_start;
}

void EnemyNotSoBasicGreen::Move(){

	//-----------Face Player---------------

	enemy_player_radius = position.DistanceTo(App->player->position);
	delta_y = position.y - App->player->position.y;
	delta_x = position.x - App->player->position.x;
	radius_deltax = enemy_player_radius - delta_x;

	if (radius_deltax < enemy_player_radius / 5){
		move_360.SetInitialFrame(LEFT);
		current_anim = &left;
		dir = LEFT;
	}
	else if (radius_deltax > 4 * enemy_player_radius / 5 && radius_deltax <= 6 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(UP);
			current_anim = &up;
			dir = UP;
		}
		else {
			move_360.SetInitialFrame(DOWN);
			current_anim = &down;
			dir = DOWN;
		}
	}
	else if (radius_deltax > enemy_player_radius / 5 && radius_deltax < 2 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_60);
			current_anim = &left_up;
			dir = ANGLE_60;
		}
		else {
			move_360.SetInitialFrame(ANGLE_120);
			current_anim = &left_down;
			dir = ANGLE_120;
		}
	}
	else if (radius_deltax > 2 * enemy_player_radius / 5 && radius_deltax < 3 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(LEFT_UP);
			current_anim = &left_up;
			dir = LEFT_UP;
		}
		else {
			move_360.SetInitialFrame(LEFT_DOWN);
			current_anim = &left_down;
			dir = LEFT_DOWN;
		}
	}
	else if (radius_deltax > 3 * enemy_player_radius / 5 && radius_deltax < 4 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_30);
			current_anim = &left_up;
			dir = ANGLE_30;
		}
		else {
			move_360.SetInitialFrame(ANGLE_150);
			current_anim = &left_down;
			dir = ANGLE_150;
		}
	}
	else if (radius_deltax > 6 * enemy_player_radius / 5 && radius_deltax < 7 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_330);
			current_anim = &right_up;
			dir = ANGLE_330;
		}
		else {
			move_360.SetInitialFrame(ANGLE_210);
			current_anim = &right_down;
			dir = ANGLE_210;
		}
	}
	else if (radius_deltax > 7 * enemy_player_radius / 5 && radius_deltax < 8 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(RIGHT_UP);
			current_anim = &right_up;
			dir = RIGHT_UP;
		}
		else {
			move_360.SetInitialFrame(RIGHT_DOWN);
			current_anim = &right_down;
			dir = RIGHT_DOWN;
		}
	}
	else if (radius_deltax > 8 * enemy_player_radius / 5 && radius_deltax < 9 * enemy_player_radius / 5){
		if (delta_y>0){
			move_360.SetInitialFrame(ANGLE_300);
			current_anim = &right_up;
			dir = ANGLE_300;
		}
		else {
			move_360.SetInitialFrame(ANGLE_240);
			current_anim = &right_down;
			dir = ANGLE_240;
		}
	}
	else if (radius_deltax > 9 * enemy_player_radius / 5 && radius_deltax < 2 * enemy_player_radius){
		move_360.SetInitialFrame(RIGHT);
		current_anim = &right;
		dir = RIGHT;
	}

	//-----------------------------------------------

	prev_pos = position;
	position = original + path->GetCurrentSpeed();

}

void EnemyNotSoBasicGreen::Draw(){

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (position != prev_pos){
		App->render->Blit(tex, position.x, position.y, &(current_anim->GetCurrentFrame()));
	}
	else App->render->Blit(tex, position.x, position.y, &move_360.GetActualFrame());
}

void EnemyNotSoBasicGreen::Shot(){

	now = SDL_GetTicks();

	if (now - last_shot > 3000 && (position.y - App->player->position.y >-200 && position.y - App->player->position.y < 200)){
		float x_speed = (-delta_x / enemy_player_radius) * 3;
		float y_speed = (-delta_y / enemy_player_radius) * 3;
		App->particles->SetParticleSpeed(bullet, x_speed, y_speed);
		switch (dir)
		{
		case LEFT:
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_60:
			App->particles->AddParticle(*bullet, position.x, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_UP:
			App->particles->AddParticle(*bullet, position.x + 5, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 3, position.y - 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_30:
			App->particles->AddParticle(*bullet, position.x + 8, position.y - 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case UP:
			App->particles->AddParticle(*bullet, position.x + 10, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 5, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_330:
			App->particles->AddParticle(*bullet, position.x + 19, position.y - 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 12, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_UP:
			App->particles->AddParticle(*bullet, position.x + 27, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 19, position.y - 4, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_300:
			App->particles->AddParticle(*bullet, position.x + 22, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 16, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT:
			App->particles->AddParticle(*bullet, position.x + 25, position.y + 13, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 22, position.y + 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_240:
			App->particles->AddParticle(*bullet, position.x + 21, position.y + 13, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_DOWN:
			App->particles->AddParticle(*bullet, position.x + 24, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 16, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_210:
			App->particles->AddParticle(*bullet, position.x + 20, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 12, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case DOWN:
			App->particles->AddParticle(*bullet, position.x + 10, position.y + 25, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 5, position.y + 20, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_150:
			App->particles->AddParticle(*bullet, position.x + 5, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 3, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_DOWN:
			App->particles->AddParticle(*bullet, position.x + 3, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_120:
			App->particles->AddParticle(*bullet, position.x + 3, position.y + 15, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 10, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		}
		last_shot = SDL_GetTicks();
	}
}