#include "EnemyRoomba.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include <math.h>

EnemyRoomba::EnemyRoomba(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type){
	position.x = x;
	position.y = y;
	original.x = x;
	original.y = y;

	collider = App->collisions->AddCollider({ 0, 0, 31, 32 }, COLLIDER_ENEMY, (Module*)App->enemies);

	Idle.PushBack({ 14, 16, 31, 32 });
	Idle.PushBack({ 57, 16, 31, 32 });
	Idle.speed = 0.2f;

	Fire.PushBack({ 197, 17, 30, 31 });
	Fire.PushBack({ 154, 17, 30, 31 });
	Fire.PushBack({ 106, 17, 30, 31 });
	Fire.loop = false;
	Fire.speed = 0.2f;

	Fire_end.PushBack({ 154, 17, 30, 31 });
	Fire_end.PushBack({ 197, 17, 30, 31 });
	Fire_end.loop = false;
	Fire_end.speed = 0.2f;

	hp = 6;
	points = 90;

	dead = &App->particles->green_basic_dead;

	bullet = &App->particles->green_basic_bullet;

	tex = App->particles->roomba;

	collider->SetPos(position.x, position.y);

	animation = &Idle;
}

void EnemyRoomba::Shot(){

	if (curr_state == ST_Fire && Fire.Finished()){
		CreateShots();

		animation = &Fire_end;
		Fire.Reset();
	}
	if (Fire_end.Finished()){
		change_state = true;
		Fire_end.Reset();
	}

}

void EnemyRoomba::Move(){

	if (change_state){
		switch (curr_state)
		{
		case ST_RoombaIdle:
			curr_state = ST_Fire;
			animation = &Fire;
			break;
		case ST_Fire:
			curr_state = ST_RoombaIdle;
			animation = &Idle;
			break;
		}
		change_state = false;
		cont = 0;
	}
	
	position = original + path->GetCurrentSpeed();
	collider->SetPos(position.x, position.y);

	if (cont == 59) change_state = true;

	App->render->Blit(tex, position.x,position.y,&animation->GetCurrentFrame());

	cont++;
}

void EnemyRoomba::CreateShots(){
	enemy_player_radius = position.DistanceTo(App->player->position);
	delta_y = position.y - App->player->position.y;
	delta_x = position.x - App->player->position.x;
	angle = asin(delta_y / enemy_player_radius);

	int correction = (delta_x < 0) ? 1 : -1;

	App->particles->AddParticle(App->particles->green_basic_bullet_start, position.x+10, position.y+3, COLLIDER_NONE, { 0, 0, 0, 0 });
	App->particles->SetParticleSpeed(bullet, correction*speed*cos(angle), -speed*sin(angle));
	App->particles->AddParticle(*bullet, position.x+10, position.y+3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
	App->particles->SetParticleSpeed(bullet, correction*(speed + 1)*cos(angle + M_PI / 9), -(speed + 1)*sin(angle + M_PI / 9));
	App->particles->AddParticle(*bullet, position.x + 10, position.y + 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
	App->particles->SetParticleSpeed(bullet, correction*(speed + 2)*cos(angle + 2 * M_PI / 9), -(speed + 2)*sin(angle + 2 * M_PI / 9));
	App->particles->AddParticle(*bullet, position.x + 10, position.y + 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
	App->particles->SetParticleSpeed(bullet, correction*(speed + 3)*cos(angle + 3 * M_PI / 9), -(speed + 3)*sin(angle + 3 * M_PI / 9));
	App->particles->AddParticle(*bullet, position.x + 10, position.y + 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
	App->particles->SetParticleSpeed(bullet, correction*(speed + 1)*cos(angle - M_PI / 9), -(speed + 1)*sin(angle - M_PI / 9));
	App->particles->AddParticle(*bullet, position.x + 10, position.y + 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
	App->particles->SetParticleSpeed(bullet, correction*(speed + 2)*cos(angle - 2 * M_PI / 9), -(speed + 2)*sin(angle - 2 * M_PI / 9));
	App->particles->AddParticle(*bullet, position.x + 10, position.y + 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
	App->particles->SetParticleSpeed(bullet, correction*(speed + 3)*cos(angle - 3 * M_PI / 9), -(speed + 3)*sin(angle - 3 * M_PI / 9));
	App->particles->AddParticle(*bullet, position.x + 10, position.y + 3, COLLIDER_ENEMY_SHOT, { 0, 0, 6, 6 });
}