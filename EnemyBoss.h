#ifndef _Boss_
#define _Boss_

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "p2Point.h"

enum STATES{
	ST_ShellIdle, ST_Idle, ST_EjectShell, ST_EquipShell, ST_Apear
};

class EnemyBoss:public Enemy
{
public:
	EnemyBoss(int x, int y, ENEMY_TYPES type);

	void Draw();

private:
	STATES curr_state = ST_Apear;
	bool phase_change = false;
	Enemy* adds[8];

	iPoint Shell_left_pos;
	iPoint Shell_right_pos;
	fPoint boss;
	iPoint missile1;
	iPoint missile2;
	iPoint missile3;
	iPoint missile4;

	Animation rocket_left;
	Animation explosion_left;
	Animation rocket_right;
	Animation explosion_right;
	Animation boss_idle;
	
	SDL_Rect misile;
	SDL_Rect Shell_left;
	SDL_Rect Shell_right;

	Collider* shell_left_col;
	Collider* shell_right_col;

	uint timer;
	uint now;

	float x_speed;
	float y_speed;
	float enemy_player_radius;
	float delta_y;
	float delta_x;
	bool get_speed=true;

	uint cont = 0;

private:
	void CheckState();
	void EquipMissile(int x, int missile_num);
	void SetMoveSpeed();


};



#endif