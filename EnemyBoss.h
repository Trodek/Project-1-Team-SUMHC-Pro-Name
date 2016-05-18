#ifndef _Boss_
#define _Boss_

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "p2Point.h"

enum STATES{
	ST_ShellIdle, ST_Idle, ST_EjectShell, ST_EquipShell, ST_Apear
};

class EnemyBoss
{
public:
	EnemyBoss();

	void Draw();

private:
	STATES curr_state = ST_Apear;
	bool phase_change = false;
	Enemy* adds[8];

	iPoint Shell_left_pos;
	iPoint Shell_right_pos;
	iPoint boss;

	Animation rocket_left;
	Animation explosion_left;
	Animation rocket_right;
	Animation explosion_right;
	Animation boss_idle;
	
	SDL_Rect misile;


private:
	void CheckState();


};



#endif