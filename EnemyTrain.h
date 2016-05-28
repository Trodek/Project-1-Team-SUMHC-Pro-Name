#ifndef __ENEMYTRUCK_H__
#define __ENEMYTRUCK_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class EnemyTrain : public Enemy
{
private:
	iPoint original_pos;
	Animation idle;
	
	int now;

	Particle* dead_hole;
	Path mov;

public:

	EnemyTrain(int x, int y, ENEMY_TYPES type);

	void UpdateAnim();
	void Move();
	void Draw();
};

#endif // 