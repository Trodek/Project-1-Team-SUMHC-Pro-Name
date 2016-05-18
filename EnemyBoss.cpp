#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "EnemyBoss.h"
#include "SDL/include/SDL_timer.h"

EnemyBoss::EnemyBoss(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type)
{
	boss.x = x;
	boss.y = y;

	Shell_left_pos.x = x - 64;
	Shell_left_pos.y = y - 71;

	Shell_right_pos.x = x + 32;
	Shell_right_pos.y = y - 71;

	tex = App->particles->boss;

	misile = { 128, 197, 12, 64 };
	Shell_left = { 208, 1, 96, 160 };
	Shell_right = { 104, 1, 96, 160 };

	dead = &App->particles->big_turret_dead;

	boss_idle.PushBack({ 14, 282, 64, 56 });
	boss_idle.PushBack({ 88, 282, 64, 56 });
	boss_idle.speed = 0.1f;
	boss_idle.loop = true;

	hp = 2040;
	points = 332000;

	timer = SDL_GetTicks();

	collider = App->collisions->AddCollider({ 0, 0, 64, 56 }, COLLIDER_ENEMY, (Module*)App->enemies);
	shell_left_col = App->collisions->AddCollider({ 0, 0, 96, 160 }, COLLIDER_WALL);
	shell_right_col = App->collisions->AddCollider({ 0, 0, 96, 160 }, COLLIDER_WALL);
	collider->SetPos(boss.x, boss.y);
	shell_left_col->SetPos(Shell_left_pos.x, Shell_left_pos.y);
	shell_right_col->SetPos(Shell_right_pos.x, Shell_right_pos.y);
}

void EnemyBoss::Draw(){
	CheckState();
	now = SDL_GetTicks();

	switch (curr_state)
	{
	case ST_ShellIdle:
		if (cont > 150)phase_change = true;
		cont++;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
		App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
		break;
	case ST_Idle:
		if (get_speed){
			SetMoveSpeed();
			get_speed = false;
		}
		if (cont<120){
			boss.x += x_speed;
			boss.y += y_speed;
		}
		if (cont > 150 && cont < 271){
			boss.x -= x_speed;
			boss.y -= y_speed;
		}
		if (cont == 271){
			get_speed = true;
		}
		if (cont > 271 && cont < 391){
			boss.x += x_speed;
			boss.y += y_speed;
		}
		if (cont > 421 && cont < 541){
			boss.x -= x_speed;
			boss.y -= y_speed;
		}
		if (cont>541)phase_change = true;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		cont++;
		
		break;
	case ST_EjectShell:
		if (cont > 150)phase_change = true;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		if (cont < 150){
			App->render->Blit(tex, Shell_left_pos.x--, Shell_left_pos.y--, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x++, Shell_right_pos.y--, &Shell_right);
		}
		cont++;
		break;
	case ST_EquipShell:
		App->render->Blit(tex, (int)boss.x, (int)boss.y, &(boss_idle.GetCurrentFrame()));
		if (Shell_right_pos.x !=(int)boss.x+32){
			App->render->Blit(tex, Shell_left_pos.x++, Shell_left_pos.y++, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x--, Shell_right_pos.y++, &Shell_right);
		}
		else {
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
			phase_change = true;
		}
		cont++;
		break;
	case ST_Apear:
		if (cont < 90){
			App->render->Blit(tex, boss.x, boss.y++, &(boss_idle.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y++, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y++, &Shell_right);
		}
		else if (cont < 150){
			App->render->Blit(tex, boss.x, boss.y--, &(boss_idle.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y--, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y--, &Shell_right);
		}
		else phase_change = true;
		
		cont++; 
		break;
	default:
		break;
	}
	collider->SetPos(boss.x, boss.y);
	shell_left_col->SetPos(Shell_left_pos.x, Shell_left_pos.y);
	shell_right_col->SetPos(Shell_right_pos.x, Shell_right_pos.y);

	position.x = boss.x;
	position.y = boss.y;
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