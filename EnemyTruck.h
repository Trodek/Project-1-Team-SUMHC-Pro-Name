#ifndef __ENEMYTRUCK_H__
#define __ENEMYTRUCK_H__

#include "Enemy.h"
#include "Path.h"

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

	EnemyTruck(int x, int y);

	void UpdateAnim();
	void Move();
};

#endif // 