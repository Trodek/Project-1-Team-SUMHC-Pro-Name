#ifndef __Enemy_NotBasic__
#define __Enemy_NotBasic__

#include "Enemy.h"
#include "Globals.h"
#include "ModuleEnemies.h"

class EnemyNotSoBasic : public Enemy
{
private:

	iPoint original;
	iPoint prev_pos;

	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation left_up;
	Animation left_down;
	Animation right_up;
	Animation right_down;
	Animation move_360;

	Animation* current_anim;

	int now;
	int last_shot;

	Particle* bullet;
	Particle* shoot_start;

	Direction dir = IDLE;

	float enemy_player_radius;
	float delta_y;
	float delta_x;
	float radius_deltax;

public:

	EnemyNotSoBasic(int x, int y, ENEMY_TYPES type);

	void Shot();
	void Move();
	void Draw();
};

#endif // 