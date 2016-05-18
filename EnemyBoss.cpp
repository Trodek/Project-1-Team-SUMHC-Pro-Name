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
	//Positions
	boss.x = x;
	boss.y = y;

	Shell_left_pos.x = x - 64;
	Shell_left_pos.y = y - 71;

	Shell_right_pos.x = x + 32;
	Shell_right_pos.y = y - 71;

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

	hp = 2040;
	points = 332000;


	collider = App->collisions->AddCollider({ 0, 0, 64, 56 }, COLLIDER_ENEMY, (Module*)App->enemies);
	shell_left_col = App->collisions->AddCollider({ 0, 0, 96, 160 }, COLLIDER_PASS_BULLET);
	shell_right_col = App->collisions->AddCollider({ 0, 0, 96, 160 }, COLLIDER_PASS_BULLET);
	collider->SetPos(boss.x, boss.y);
	shell_left_col->SetPos(Shell_left_pos.x, Shell_left_pos.y);
	shell_right_col->SetPos(Shell_right_pos.x, Shell_right_pos.y);

	App->player->scroll = false;
}

void EnemyBoss::Draw(){
	CheckState();

	switch (curr_state)
	{
	case ST_ShellIdle:
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
		if (cont > 210)phase_change = true;
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
		if (Shell_right_pos.x !=(int)boss.x+32){
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