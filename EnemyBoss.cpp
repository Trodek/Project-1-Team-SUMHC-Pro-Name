#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
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

	timer = SDL_GetTicks();

	collider = App->collisions->AddCollider({ 0, 0, 64, 56 }, COLLIDER_ENEMY);
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
		if (now - timer > 2000)phase_change = true;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
		App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
		break;
	case ST_Idle:
		if (now - timer > 2000)phase_change = true;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		break;
	case ST_EjectShell:
		if (now - timer > 1500)phase_change = true;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		if (now - timer < 1500){
			App->render->Blit(tex, Shell_left_pos.x--, Shell_left_pos.y--, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x++, Shell_right_pos.y--, &Shell_right);
		}
		break;
	case ST_EquipShell:
		if (now - timer > 2000)phase_change = true;
		App->render->Blit(tex, boss.x, boss.y, &(boss_idle.GetCurrentFrame()));
		if (Shell_right_pos.x !=boss.x+32){
			App->render->Blit(tex, Shell_left_pos.x++, Shell_left_pos.y++, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x--, Shell_right_pos.y++, &Shell_right);
		}
		else {
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y, &Shell_right);
		}
		break;
	case ST_Apear:
		if (now - timer < 2000){
			App->render->Blit(tex, boss.x, boss.y++, &(boss_idle.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y++, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y++, &Shell_right);
		}
		else if (now - timer < 3250){
			App->render->Blit(tex, boss.x, boss.y--, &(boss_idle.GetCurrentFrame()));
			App->render->Blit(tex, Shell_left_pos.x, Shell_left_pos.y--, &Shell_left);
			App->render->Blit(tex, Shell_right_pos.x, Shell_right_pos.y--, &Shell_right);
		}
		else phase_change = true;
		

		break;
	default:
		break;
	}
	collider->SetPos(boss.x, boss.y);
	shell_left_col->SetPos(Shell_left_pos.x, Shell_left_pos.y);
	shell_right_col->SetPos(Shell_right_pos.x, Shell_right_pos.y);
}

void EnemyBoss::CheckState(){
	if (phase_change){
		switch (curr_state)
		{
		case ST_ShellIdle:
			timer = SDL_GetTicks();
			curr_state = ST_EjectShell;
			phase_change = false;
			break;
		case ST_Idle:
			timer = SDL_GetTicks();
			curr_state = ST_EquipShell;
			phase_change = false;
			break;
		case ST_EjectShell:
			timer = SDL_GetTicks();
			curr_state = ST_Idle;
			phase_change = false;
			break;
		case ST_EquipShell:
			timer = SDL_GetTicks();
			curr_state = ST_ShellIdle;
			phase_change = false;
			break;
		case ST_Apear:
			timer = SDL_GetTicks();
			curr_state = ST_ShellIdle;
			phase_change = false;
			break;
		}
	}
}