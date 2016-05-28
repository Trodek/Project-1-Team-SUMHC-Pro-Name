#ifndef __Enemy_Big_Turret__
#define __Enemy_Big_Turret__

#include "Enemy.h"
#include "ModuleEnemies.h"

class EnemyBigTurret : public Enemy
{
private:
	
	Animation idle;
	Animation damaged;
	Animation damaged2;

	int now;
	int last_shot;

	Particle* turret_bullet;
	Particle* shoot_start;

	int count = 0;
	bool increase = true;

public:

	EnemyBigTurret(int x, int y, ENEMY_TYPES type);

	void UpdateAnim();
	void Shot();
	void Draw();
};

#endif // 