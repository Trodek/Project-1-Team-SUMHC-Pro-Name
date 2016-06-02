#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "EnemyBoss.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>

EnemyBoss::EnemyBoss(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type)
{
	//Positions
	boss.x = x;
	boss.y = y;

	Shell_left_pos.x = x - 64;
	Shell_left_pos.y = y - 71;

	Shell_right_pos.x = x + 32;
	Shell_right_pos.y = y - 71;

	twister1.x = twister2.x = twister3.x = twister4.x = twister5.x = twister6.x = twister7.x = twister8.x = x;
	twister1.y = twister2.y = twister3.y = twister4.y = twister5.y = twister6.y = twister7.y = twister8.y = y;

	//texture
	tex = App->particles->boss;

	//static sprites
	missile = { 46, 197, 16, 64 };
	Shell_left = { 208, 1, 96, 160 };
	Shell_right = { 107, 1, 96, 160 };

	// dead particle
	dead = &App->particles->truck_dead;

	//Animations
	boss_idle.PushBack({ 14, 282, 64, 56 });
	boss_idle.PushBack({ 88, 282, 64, 56 });
	boss_idle.speed = 0.15f;
	boss_idle.loop = true;

	rocket_right.PushBack({ 1, 79, 53, 77 });
	rocket_right.PushBack({ 53, 79, 53, 77 });
	rocket_right.speed = 0.7f;

	rocket_left.PushBack({ 1, 1, 53, 77 });
	rocket_left.PushBack({ 52, 1, 53, 77 });
	rocket_left.speed = 0.7f;

	explosion_right.PushBack({ 356, 323, 30, 72 });
	explosion_right.PushBack({ 281, 323, 30, 72 });
	explosion_right.speed = 0.7f;

	explosion_left.PushBack({ 356, 244, 30, 72 });
	explosion_left.PushBack({ 291, 244, 30, 72 });
	explosion_left.speed = 0.7f;

	twister.PushBack({ 168, 191, 34, 34 });
	twister.PushBack({ 206, 192, 34, 34 });
	twister.PushBack({ 246, 193, 34, 34 });
	twister.PushBack({ 282, 192, 34, 34 });
	twister.speed = 0.7f;

	hp = 2040;
	points = 332000;

	//colliders

	collider = App->collisions->AddCollider({ 0, 0, 64, 56 }, COLLIDER_ENEMY, (Module*)App->enemies);
	shell_left_col = App->collisions->AddCollider({ 0, 0, 96, 160 }, COLLIDER_PASS_BULLET);
	shell_right_col = App->collisions->AddCollider({ 0, 0, 96, 160 }, COLLIDER_PASS_BULLET);
	twister1_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister2_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister3_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister4_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister5_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister6_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister7_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);
	twister8_col = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, (Module*)App->enemies);

	collider->SetPos(boss.x, boss.y);
	shell_left_col->SetPos(Shell_left_pos.x, Shell_left_pos.y);
	shell_right_col->SetPos(Shell_right_pos.x, Shell_right_pos.y);
	twister1_col->SetPos(twister1.x, twister1.y);

	App->player->scroll = false;

	App->collisions->matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = true;
	App->collisions->matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = true;
	App->collisions->matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER_SHOT] = true;
	App->collisions->matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PASS_BULLET] = true;
}

void EnemyBoss::Draw(){
	CheckState();

	switch (curr_state)
	{
	case ST_ShellIdle:
		twister1_col->SetPos(0, -50);
		twister2_col->SetPos(0, -50);
		twister3_col->SetPos(0, -50);
		twister4_col->SetPos(0, -50);
		twister5_col->SetPos(0, -50);
		twister6_col->SetPos(0, -50);
		twister7_col->SetPos(0, -50);
		twister8_col->SetPos(0, -50);

		if (cont > 210)phase_change = true;
		if (cont < 60){
			boss.y--;
			Shell_left_pos.y--;
			Shell_right_pos.y--;
		}
		else if (cont == 60){
			missile1.x = boss.x - 23;
			missile1.y = boss.y - 1;
			missile2.x = boss.x + 9;
			missile2.y = boss.y;
			missile3.x = boss.x + 41;
			missile3.y = boss.y - 15;
			missile4.x = boss.x + 73;
			missile4.y = boss.y - 46;
		}
		else if (cont < 210){
			if (cont <75 ){
				missile1.y++;
			}
			if (cont <90){
				missile2.y++;
			}
			if (cont <105){
				missile3.y++;
			}
			if (cont <120){
				missile4.y++;
			}
			if (cont<140){
				App->render->Blit(tex, missile1.x, missile1.y, &missile);
			}
			if (cont==140){
				App->particles->AddParticle(App->particles->missile, missile1.x, missile1.y, COLLIDER_ENEMY_SHOT, { 0, 0, 16, 64 });
			}
			if (cont<163){
				App->render->Blit(tex, missile2.x, missile2.y, &missile);
			}
			if (cont == 163){
				App->particles->AddParticle(App->particles->missile, missile2.x, missile2.y, COLLIDER_ENEMY_SHOT, { 0, 0, 16, 64 });
			}
			if (cont<186){
				App->render->Blit(tex, missile3.x, missile3.y, &missile);
			}
			if (cont == 186){
				App->particles->AddParticle(App->particles->missile, missile3.x, missile3.y, COLLIDER_ENEMY_SHOT, { 0, 0, 16, 64 });
			}
			if (cont<209){
				App->render->Blit(tex, missile4.x, missile4.y, &missile);
			}
			if (cont == 209){
				App->particles->AddParticle(App->particles->missile, missile4.x, missile4.y, COLLIDER_ENEMY_SHOT, { 0, 0, 16, 64 });
			}
		}
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		App->render->Blit(tex, Shell_left_pos.x-23, Shell_left_pos.y+20, &(rocket_left.GetCurrentFrame()));
		App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
		App->render->Blit(tex, Shell_right_pos.x+67, Shell_right_pos.y+20, &(rocket_right.GetCurrentFrame()));
		App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
		cont++;
		break;
	case ST_Idle:
		if (get_speed){
			SetMoveSpeed();
			get_speed = false;
		}
		if (cont<120){
			boss.x += x_speed;
			boss.y += y_speed;
			radius+= 0.5f;
		}
		if (cont > 150 && cont < 271){
			boss.x -= x_speed;
			boss.y -= y_speed;
			radius-=0.5f;
		}
		if (cont == 271){
			get_speed = true;
		}
		if (cont > 271 && cont < 391){
			boss.x += x_speed;
			boss.y += y_speed;
			radius += 0.5f;
		}
		if (cont > 421 && cont < 541){
			boss.x -= x_speed;
			boss.y -= y_speed;
			radius -= 0.5f;
		}
		if (cont>541)phase_change = true;

		MoveBall(twister1, boss.x + 15, boss.y + 11, radius, steps, twister1_col);
		MoveBall(twister2, boss.x + 15, boss.y + 11, radius, steps + M_PI / 4, twister2_col);
		MoveBall(twister3, boss.x + 15, boss.y + 11, radius, steps + M_PI / 2, twister3_col);
		MoveBall(twister4, boss.x + 15, boss.y + 11, radius, steps + 3 * M_PI / 4, twister4_col);
		MoveBall(twister5, boss.x + 15, boss.y + 11, radius, steps + M_PI, twister5_col);
		MoveBall(twister6, boss.x + 15, boss.y + 11, radius, steps + 5 * M_PI / 4, twister6_col);
		MoveBall(twister7, boss.x + 15, boss.y + 11, radius, steps + 3 * M_PI / 2, twister7_col);
		MoveBall(twister8, boss.x + 15, boss.y + 11, radius, steps + 7 * M_PI / 4, twister8_col);
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		cont++;
		
		break;
	case ST_EjectShell:
		if (cont > 210)phase_change = true;
		radius = 40;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		
		if (cont < 60){
			App->render->Blit(tex, Shell_left_pos.x - 23, Shell_left_pos.y + 20, &(rocket_left.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x + 67, Shell_right_pos.y + 20, &(rocket_right.GetCurrentFrame()));
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
			boss.y++;
			Shell_left_pos.y++;
			Shell_right_pos.y++;	
		}
		else if (cont < 210){
			MoveBall(twister1, boss.x + 15, boss.y + 11, radius, steps, twister1_col);
			MoveBall(twister2, boss.x + 15, boss.y + 11, radius, steps + M_PI / 4, twister2_col);
			MoveBall(twister3, boss.x + 15, boss.y + 11, radius, steps + M_PI / 2, twister3_col);
			MoveBall(twister4, boss.x + 15, boss.y + 11, radius, steps + 3 * M_PI / 4, twister4_col);
			MoveBall(twister5, boss.x + 15, boss.y + 11, radius, steps + M_PI, twister5_col);
			MoveBall(twister6, boss.x + 15, boss.y + 11, radius, steps + 5 * M_PI / 4, twister6_col);
			MoveBall(twister7, boss.x + 15, boss.y + 11, radius, steps + 3 * M_PI / 2, twister7_col);
			MoveBall(twister8, boss.x + 15, boss.y + 11, radius, steps + 7 * M_PI / 4, twister8_col);

			App->render->Blit(tex, Shell_left_pos.x - 23, Shell_left_pos.y + 20, &(rocket_left.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x + 89 , Shell_left_pos.y + 52, &(explosion_left.GetCurrentFrame()));
			App->render->Blit(tex, Shell_right_pos.x-24, Shell_right_pos.y+52, &(explosion_right.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x--, Shell_left_pos.y--, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x + 67, Shell_right_pos.y + 20, &(rocket_right.GetCurrentFrame()));
			App->render->Blit(tex, Shell_right_pos.x++, Shell_right_pos.y--, &Shell_right);
		}
		cont++;
		break;
	case ST_EquipShell:
		App->render->Blit(tex, (int)boss.x, (int)boss.y, &(boss_idle.GetCurrentFrame()));
		radius = 40;
		if (Shell_right_pos.x !=(int)boss.x+32){
			MoveBall(twister1, boss.x + 15, boss.y + 11, radius, steps, twister1_col);
			MoveBall(twister2, boss.x + 15, boss.y + 11, radius, steps + M_PI / 4, twister2_col);
			MoveBall(twister3, boss.x + 15, boss.y + 11, radius, steps + M_PI / 2, twister3_col);
			MoveBall(twister4, boss.x + 15, boss.y + 11, radius, steps + 3 * M_PI / 4, twister4_col);
			MoveBall(twister5, boss.x + 15, boss.y + 11, radius, steps + M_PI, twister5_col);
			MoveBall(twister6, boss.x + 15, boss.y + 11, radius, steps + 5 * M_PI / 4, twister6_col);
			MoveBall(twister7, boss.x + 15, boss.y + 11, radius, steps + 3 * M_PI / 2, twister7_col);
			MoveBall(twister8, boss.x + 15, boss.y + 11, radius, steps + 7 * M_PI / 4, twister8_col);

			App->render->Blit(tex, Shell_left_pos.x - 23, Shell_left_pos.y + 20, &(rocket_left.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x++, Shell_left_pos.y++, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x + 67, Shell_right_pos.y + 20, &(rocket_right.GetCurrentFrame()));
			App->render->Blit(tex, Shell_right_pos.x--, Shell_right_pos.y++, &Shell_right);
		}
		else {
			App->render->Blit(tex, Shell_left_pos.x - 23, Shell_left_pos.y + 20, &(rocket_left.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x + 67, Shell_right_pos.y + 20, &(rocket_right.GetCurrentFrame()));
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
			phase_change = true;
		}
		
		cont++;
		break;
	case ST_Apear:
		if (cont < 150){
			App->render->Blit(tex, boss.x, boss.y++, &(boss_idle.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x - 23, Shell_left_pos.y + 20, &(rocket_left.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y++, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x + 67, Shell_right_pos.y + 20, &(rocket_right.GetCurrentFrame()));
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y++, &Shell_right);
		}
		else phase_change = true;
		
		cont++; 
		break;
	default:
		break;
	}

	steps += 0.01f;

	collider->SetPos(boss.x, boss.y);
	shell_left_col->SetPos(Shell_left_pos.x, Shell_left_pos.y);
	shell_right_col->SetPos(Shell_right_pos.x, Shell_right_pos.y);

	position.x = boss.x;
	position.y = boss.y;
}

void EnemyBoss::MoveBall(iPoint peg, int x, int y, float r, float t, Collider* peg_col) {
	peg.x = x + r*cos((float)t);
	peg.y = y + r*sin((float)t);
	peg_col->SetPos(peg.x+12, peg.y+12);
	App->render->Blit(tex, peg.x, peg.y, &(twister.GetCurrentFrame()));
}

void EnemyBoss::CheckState(){
	if (phase_change){
		cont = 0;
		phase_change = false;
		switch (curr_state)
		{
		case ST_ShellIdle:
			curr_state = ST_EjectShell;	
			break;
		case ST_Idle:
			get_speed = true;
			curr_state = ST_EquipShell;
			break;
		case ST_EjectShell:
			curr_state = ST_Idle;
			break;
		case ST_EquipShell:
			curr_state = ST_ShellIdle;
			break;
		case ST_Apear:
			curr_state = ST_ShellIdle;
			break;
		}
	}
}

void EnemyBoss::SetMoveSpeed(){
	enemy_player_radius = position.DistanceTo(App->player->position);
	delta_y = (boss.y - App->player->position.y);
	delta_x = (boss.x - App->player->position.x);
	
	x_speed = (-delta_x / enemy_player_radius);
	y_speed = (-delta_y / enemy_player_radius);
}

void EnemyBoss::DeleteAll(){
	App->collisions->EraseCollider(twister1_col);
	App->collisions->EraseCollider(twister2_col);
	App->collisions->EraseCollider(twister3_col);
	App->collisions->EraseCollider(twister4_col);
	App->collisions->EraseCollider(twister5_col);
	App->collisions->EraseCollider(twister6_col);
	App->collisions->EraseCollider(twister7_col);
	App->collisions->EraseCollider(twister8_col);
	App->collisions->EraseCollider(shell_left_col);
	App->collisions->EraseCollider(shell_right_col);
	App->collisions->matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	App->collisions->matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	App->collisions->matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER_SHOT] = false;
	App->collisions->matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PASS_BULLET] = false;
}