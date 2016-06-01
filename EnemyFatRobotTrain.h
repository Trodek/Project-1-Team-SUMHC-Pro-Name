#ifndef __Enemy_FatRobotTrain__
#define __Enemy_FatRobotTrain__

#include "Enemy.h"
#include "Globals.h"
#include "ModuleEnemies.h"

class EnemyFatRobotTrain : public Enemy
{
private:

	iPoint original;

	Animation idle;

	int now;
	int last_shot;

	Particle* bullet;
	Particle* shoot_start;

public:

	EnemyFatRobotTrain(int x, int y, ENEMY_TYPES type);

	void Shot();
	void Move();
	void Draw();
};

#endif // 