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
	up.PushBack({ 186, 311, 26, 36 });
	up.PushBack({ 220, 310, 27, 37 });
	up.PushBack({ 255, 312, 26, 35 });
	up.PushBack({ 289, 312, 26, 35 });
	up.speed = 0.2f;

	//char right
	right.PushBack({ 19, 221, 28, 32 });
	right.PushBack({ 58, 219, 25, 32 });
	right.PushBack({ 95, 220, 27, 32 });
	right.PushBack({ 135, 219, 25, 33 });
	right.speed = 0.25f;

	//char left
	left.PushBack({ 186, 221, 25, 32 });
	left.PushBack({ 223, 221, 28, 32 });
	left.PushBack({ 260, 220, 25, 33 });
	left.PushBack({ 297, 221, 25, 33 });
	left.speed = 0.25f;

	//char down
	down.PushBack({ 19, 311, 27, 35 });
	down.PushBack({ 57, 314, 27, 32 });
	down.PushBack({ 95, 313, 32, 33 });
	down.PushBack({ 134, 315, 27, 31 });
	down.speed = 0.2f;

	//char left-up
	left_up.PushBack({ 188, 172, 26, 35 });
	left_up.PushBack({ 222, 172, 28, 35 });
	left_up.PushBack({ 258, 170, 28, 34 });
	left_up.PushBack({ 297, 170, 27, 33 });
	left_up.speed = 0.2f;

	// char left-down
	left_down.PushBack({ 186, 265, 27, 33 });
	left_down.PushBack({ 224, 265, 27, 34 });
	left_down.PushBack({ 260, 264, 25, 34 });
	left_down.PushBack({ 291, 265, 28, 34 });
	left_down.speed = 0.2f;

	// char right-down
	right_down.PushBack({ 19, 265, 27, 34 });
	right_down.PushBack({ 54, 266, 26, 33 });
	right_down.PushBack({ 91, 266, 27, 33 });
	right_down.PushBack({ 129, 266, 26, 35 });
	right_down.speed = 0.2f;

	// char right-up
	right_up.PushBack({ 16, 173, 29, 34 });
	right_up.PushBack({ 57, 173, 26, 34 });
	right_up.PushBack({ 96, 173, 24, 33 });
	right_up.PushBack({ 131, 171, 25, 36 });
	right_up.speed = 0.2f;

	//laser 360º
	move_360.PushBack({ 125, 81, 23, 33 });  //-- left
	move_360.PushBack({ 185, 79, 24, 35 }); //-- left-up
	move_360.PushBack({ 224, 77, 27, 35 }); //-- left-up
	move_360.PushBack({ 263, 77, 26, 35 }); //-- left-up
	move_360.PushBack({ 298, 76, 28, 35 });  //-- up
	move_360.PushBack({ 300, 122, 28, 36 });  //-- right-up
	move_360.PushBack({ 265, 123, 25, 35 });  //-- right-up
	move_360.PushBack({ 229, 123, 21, 36 });  //-- right-up
	move_360.PushBack({ 188, 124, 24, 35 });  //-- right
	move_360.PushBack({ 125, 124, 26, 35 });  //-- right-down
	move_360.PushBack({ 89, 126, 27, 35 });  //-- right-down
	move_360.PushBack({ 52, 126, 29, 34 });  //-- right-down
	move_360.PushBack({ 17, 125, 28, 35 });  //-- down
	move_360.PushBack({ 19, 81, 26, 35 });  //-- left-down
	move_360.PushBack({ 54, 80, 27, 36 });  //-- left-down
	move_360.PushBack({ 90, 81, 26, 35 });  //-- left-down
	move_360.speed = 0.6f;
	move_360.SetInitialFrame(DOWN);

	tex = App->particles->green_basic;

	last_shot = SDL_GetTicks();

	dead = &App->particles->green_basic_dead;

	hp = 6;
	points = 390;
	collider = App->collisions->AddCollider({ 0, 0, 23, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	bullet = &App->particles->green_basic_bullet;
	shoot_start = &App->particles->green_basic_bullet_start;
}

void EnemyGreenBasic::Move(){

	//-----------Face Player---------------

	float enemy_player_radius = position.DistanceTo(App->player->position);
	float delta_y = position.y - App->player->position.y;
	float delta_x = position.x - App->player->position.x;
	float radius_deltax = enemy_player_radius - delta_x;

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

	if (now - last_shot > 2000 && (position.y - App->player->position.y >-500 && position.y - App->player->position.y < 500)){
		switch (dir)
		{
		case LEFT:
			App->particles->SetParticleSpeed(bullet, -3, 0);
			App->particles->AddParticle(*bullet, position.x, position.y+10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x-8, position.y+5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_60:
			App->particles->SetParticleSpeed(bullet, -2, -1);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_UP:
			App->particles->SetParticleSpeed(bullet, -2, -2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_30:
			App->particles->SetParticleSpeed(bullet, -1, -2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case UP:
			App->particles->SetParticleSpeed(bullet, 0, -3);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_330:
			App->particles->SetParticleSpeed(bullet, 1, -2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_UP:
			App->particles->SetParticleSpeed(bullet, 2, -2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_300:
			App->particles->SetParticleSpeed(bullet, 2, -1);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT:
			App->particles->SetParticleSpeed(bullet, 3, 0);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_240:
			App->particles->SetParticleSpeed(bullet, 2, 1);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case RIGHT_DOWN:
			App->particles->SetParticleSpeed(bullet, 2, 2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_210:
			App->particles->SetParticleSpeed(bullet, 1, 2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case DOWN:
			App->particles->SetParticleSpeed(bullet, 0, 3);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_150:
			App->particles->SetParticleSpeed(bullet, -1, 2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case LEFT_DOWN:
			App->particles->SetParticleSpeed(bullet, -2, 2);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		case ANGLE_120:
			App->particles->SetParticleSpeed(bullet, -2, 1);
			App->particles->AddParticle(*bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT, { 0, 0, 8, 8 });
			App->particles->AddParticle(*shoot_start, position.x - 8, position.y + 5, COLLIDER_NONE, { 0, 0, 0, 0 });
			break;
		}
		last_shot = SDL_GetTicks();
	}
}