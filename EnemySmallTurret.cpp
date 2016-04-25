#include "Application.h"
#include "Globals.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Enemy.h"
#include "ModulePlayer.h"
#include "EnemySmallTurret.h"
#include "SDL/include/SDL_timer.h"

EnemySmallTurret::EnemySmallTurret(int x, int y, ENEMY_TYPES type): Enemy(x,y,type){

	move_360.PushBack({ 157, 80, 30, 47 });
	move_360.PushBack({ 205, 80, 30, 47 });
	move_360.PushBack({ 251, 80, 30, 47 });
	move_360.PushBack({ 296, 80, 30, 47 });
	move_360.PushBack({ 341, 80, 30, 47 });
	move_360.PushBack({ 340, 135, 30, 47 });
	move_360.PushBack({ 298, 135, 30, 47 });
	move_360.PushBack({ 251, 135, 30, 47 });
	move_360.PushBack({ 205, 135, 30, 47 });
	move_360.PushBack({ 160, 135, 30, 47 });
	move_360.PushBack({ 114, 135, 30, 47 });
	move_360.PushBack({ 68, 137, 30, 47 });
	move_360.PushBack({ 21, 137, 30, 47 });
	move_360.PushBack({ 24, 81, 30, 47 });
	move_360.PushBack({ 69, 81, 30, 47 });
	move_360.PushBack({ 113, 80, 30, 47 });

	tex = App->particles->small_turret;

	collider = App->collisions->AddCollider({ 0, 0, 30, 47 }, COLLIDER_ENEMY, (Module*)App->enemies);
	collider->SetPos(position.x, position.y);

	hp = 12;
	points = 410;

	dead = &App->particles->green_basic_dead;

	bullet = &App->particles->green_basic_bullet;
	shoot_start = &App->particles->green_basic_bullet_start;
}

void EnemySmallTurret::Move(){
	enemy_player_radius = position.DistanceTo(App->player->position);
	delta_y = position.y - App->player->position.y;
	delta_x = position.x - App->player->position.x;
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

}

void EnemySmallTurret::Shot(){
	now = SDL_GetTicks();

	if (now - last_shot > 2000 && (position.y - App->player->position.y >-200 && position.y - App->player->position.y < 200)){
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

void EnemySmallTurret::Draw(){
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(tex, position.x, position.y, &move_360.GetActualFrame());
}