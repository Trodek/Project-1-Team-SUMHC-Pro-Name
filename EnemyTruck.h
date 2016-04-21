#ifndef __ENEMYTRUCK_H__
#define __ENEMYTRUCK_H__

#include "Enemy.h"

class EnemyTruck : public Enemy
{
private:

	Animation run;
	Animation damaged;
	int now;
	int last_footprint;

	Particle* footprint;

public:

	EnemyTruck(int x, int y);

	void UpdateAnim();
	void Move();
};

#endif // 