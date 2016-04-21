#ifndef __Enemy_Big_Turret__
#define __Enemy_Big_Turret__

#include "Enemy.h"

class EnemyBigTurret : public Enemy
{
private:
	
	Animation idle;
	Animation damaged;
	int now;
	int last_shot;

	Particle* turret_bullet;
	Particle* shoot_start;

public:

	EnemyBigTurret(int x, int y);

	void UpdateAnim();
	void Shot();
};

#endif // 