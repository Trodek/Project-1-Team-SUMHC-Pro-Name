#ifndef __Enemy_BlueBasic__
#define __Enemy_BlueBasic__

#include "Enemy.h"
#include "Globals.h"
#include "ModuleEnemies.h"

class EnemyBlueBasic : public Enemy
{
private:

	iPoint original;

	Animation move_360;

	Animation* current_anim;

	int now;
	int last_shot;

	Particle* bullet;
	Particle* shoot_start;

	Direction dir = IDLE;

	float enemy_player_radius;
	float delta_y;
	float delta_x;
	float radius_deltax;

public:

	EnemyBlueBasic(int x, int y, ENEMY_TYPES type);

	void Shot();
	void Move();
	void Draw();
};

#endif // 