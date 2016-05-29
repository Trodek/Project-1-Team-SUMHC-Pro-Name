#ifndef _StrangeLarge_
#define _StrangeLarge_

#include "Enemy.h"

class EnemyStrangeLarge :public Enemy{
private:

	iPoint original;

	Particle* blaster;
	Particle* shot;

	uint cont;

	Animation Idle;

public:
	EnemyStrangeLarge(int x, int y, ENEMY_TYPES types);
	void Shot();
	void Draw();

};

#endif