#ifndef __ENEMYTRUCK_H__
#define __ENEMYTRUCK_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class EnemyTruck : public Enemy
{
private:
	iPoint original_pos;
	Animation run;
	
	int now;
	int last_footprint;

	Particle* footprint;
	Particle* dead_hole;
	Path mov;

public:

	EnemyTruck(int x, int y, ENEMY_TYPES type);

	void UpdateAnim();
	void Move();
};

#endif // 