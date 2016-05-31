#ifndef _MissileThrower_
#define _MissileThrower_

#include "Enemy.h"

class EnemyMissileThrower : public Enemy{
private:
	iPoint original;

	Animation Idle;

	Particle* missile;

	uint cont = 0;


public:
	EnemyMissileThrower(int x, int y, ENEMY_TYPES types);
	void Shot();
	void Draw();
};

#endif