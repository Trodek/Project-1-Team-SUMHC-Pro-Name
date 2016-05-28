#include "Application.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "EnemyGreenBasic.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"

EnemyGreenBasic::EnemyGreenBasic(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type){

	original = position;

	dir = IDLE;

	//Char Up anim
	up.PushBack({ 0, 74, 31, 37 });
	up.PushBack({ 31, 74, 31, 37 });
	up.PushBack({ 62, 74, 31, 37 });
	up.PushBack({ 93, 74, 31, 37 });
	up.speed = 0.05f;

	//char right
	right.PushBack({ 0, 111, 31, 37 });
	right.PushBack({ 31, 111, 31, 37 });
	right.PushBack({ 62, 111, 31, 37 });
	right.PushBack({ 93, 111, 31, 37 });
	right.speed = 0.07f;

	//char left
	left.PushBack({ 0, 37, 31, 37 });
	left.PushBack({ 31, 37, 31, 37 });
	left.PushBack({ 62, 37, 31, 37 });
	left.PushBack({ 93, 37, 31, 37 });
	left.speed = 0.07f;

	//char down
	down.PushBack({ 0, 0, 31, 37 });
	down.PushBack({ 31, 0, 31, 37 });
	down.PushBack({ 62, 0, 31, 37 });
	down.PushBack({ 93, 0, 31, 37 });
	down.speed = 0.07f;

	//char left-up
	left_up.PushBack({ 124, 37, 31, 37 });
	left_up.PushBack({ 155, 37, 31, 37 });
	left_up.PushBack({ 186, 37, 31, 37 });
	left_up.PushBack({ 217, 37, 31, 37 });
	left_up.speed = 0.05f;

	// char left-down
	left_down.PushBack({ 124, 0, 31, 37 });
	left_down.PushBack({ 155, 0, 31, 37 });
	left_down.PushBack({ 186, 0, 31, 37 });
	left_down.PushBack({ 217, 0, 31, 37 });
	left_down.speed = 0.05f;

	// char right-down
	right_down.PushBack({ 124, 111, 31, 37 });
	right_down.PushBack({ 155, 111, 31, 37 });
	right_down.PushBack({ 186, 111, 31, 37 });
	right_down.PushBack({ 217, 111, 31, 37 });
	right_down.speed = 0.05f;

	// char right-up
	right_up.PushBack({ 124, 74, 31, 37 });
	right_up.PushBack({ 155, 74, 31, 37 });
	right_up.PushBack({ 186, 74, 31, 37 });
	right_up.PushBack({ 217, 74, 31, 37 });
	right_up.speed = 0.05f;

	//move 360º
	move_360.PushBack({ 128, 148, 32, 37 });  //-- left
	move_360.PushBack({ 96, 148, 32, 37 }); //-- left-up
	move_360.PushBack({ 64, 148, 32, 37 }); //-- left-up
	move_360.PushBack({ 32, 148, 32, 37 }); //-- left-up
	move_360.PushBack({ 0, 148, 32, 37 });  //-- up
	move_360.PushBack({ 224, 185, 32, 37 });  //-- right-up
	move_360.PushBack({ 192, 185, 32, 37 });  //-- right-up
	move_360.PushBack({ 160, 185, 32, 37 });  //-- right-up
	move_360.PushBack({ 128, 185, 32, 37 });  //-- right
	move_360.PushBack({ 96, 185, 32, 37 });  //-- right-down
	move_360.PushBack({ 64, 185, 32, 37 });  //-- right-down
	move_360.PushBack({ 32, 185, 32, 37 });  //-- right-down
	move_360.PushBack({ 0, 185, 32, 37 });  //-- down
	move_360.PushBack({ 224, 148, 32, 37 });  //-- left-down
	move_360.PushBack({ 192, 148, 32, 37 });  //-- left-down
	move_360.PushBack({ 160, 148, 32, 37 });  //-- left-down
	move_360.speed = 0.6f;
	move_360.SetInitialFrame(DOWN);

	tex = App->particles->green_basic;

	last_shot = SDL_GetTicks();

	dead = &App->particles->green_basic_dead;

	hp = 6;
	points = 390;
	collider = App->collisions->AddCollider({ 0, 0, 23, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);
	bullet = &App->particles->green_basic_bullet;
	shoot_start = &App->particles->green_basic_bullet_start;
}

void EnemyGreenBasic::Move(){

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
	else if (radius_deltax > 4 * enemy_player_radius / 5 && radius_deltax <= 6*enemy_player_radius/5){
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

void EnemyGreenBasic::Draw(){
	
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (position != prev_pos){
		App->render->Blit(tex, position.x, position.y, &(current_anim->GetCurrentFrame()));
	}
	else App->render->Blit(tex, position.x, position.y, &move_360.GetActualFrame());
}

void EnemyGreenBasic::Shot(){

	now = SDL_GetTicks();

	if (now - last_shot > 3000 && (position.y - App->player->position.y >-200 && position.y - App->player->position.y < 200)){
		float x_speed = (-delta_x / enemy_player_radius)*3;
		float y_speed = (-delta_y / enemy_player_radius)*3;
		App->particles->SetParticleSpeed(bullet, x_speed, y_speed);
		switch (dir)
		{
		case LEFT:
			App->particles->AddParticle(*bullet, position.x, position.y+10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x-8, position.y+5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_60:
			App->particles->AddParticle(*bullet, position.x, position.y + 5, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_UP:
			App->particles->AddParticle(*bullet, position.x+5, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 3, position.y -5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_30:
			App->particles->AddParticle(*bullet, position.x+8, position.y -3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +1, position.y -8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case UP:
			App->particles->AddParticle(*bullet, position.x+10, position.y, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x+5 , position.y-8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_330:
			App->particles->AddParticle(*bullet, position.x+19, position.y-3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +12, position.y - 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_UP:
			App->particles->AddParticle(*bullet, position.x+27, position.y , COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +19, position.y - 4, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_300:
			App->particles->AddParticle(*bullet, position.x+22, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 16, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT:
			App->particles->AddParticle(*bullet, position.x+25, position.y + 13, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +22, position.y + 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_240:
			App->particles->AddParticle(*bullet, position.x + 21, position.y + 13, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 8, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_DOWN:
			App->particles->AddParticle(*bullet, position.x+24, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +16, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_210:
			App->particles->AddParticle(*bullet, position.x+20, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +12, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case DOWN:
			App->particles->AddParticle(*bullet, position.x+10, position.y + 25, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x +5, position.y + 20, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_150:
			App->particles->AddParticle(*bullet, position.x+5, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 3, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_DOWN:
			App->particles->AddParticle(*bullet, position.x+3, position.y + 20, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 15, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_120:
			App->particles->AddParticle(*bullet, position.x+3, position.y + 15, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
			App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 10, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		}
		last_shot = SDL_GetTicks();
	}
}