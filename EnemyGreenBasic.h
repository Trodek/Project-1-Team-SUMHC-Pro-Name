#ifndef __Enemy_GreenBasic__
#define __Enemy_GreenBasic__

#include "Enemy.h"
#include "Globals.h"
#include "ModuleEnemies.h"

class EnemyGreenBasic : public Enemy
{
private:

	iPoint original;

	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation left_up;
	Animation left_down;
	Animation right_up;
	Animation right_down;
	Animation move_360;

	int now;
	int last_shot;

	Particle* bullet;
	Particle* shoot_start;

	Direction dir;

public:

	EnemyGreenBasic(int x, int y, ENEMY_TYPES type);

	void Shot();
	void Move();
	void Draw();
};

#endif // 