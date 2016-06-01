#ifndef __Enemy_Rounded_Turret__
#define __Enemy_Rounded_Turret__

#include "Enemy.h"
#include "ModuleEnemies.h"

class EnemyRoundedTurret : public Enemy
{
private:

	Animation move_360;

	int now;
	int last_shot;

	Particle* bullet;
	Particle* shoot_start;

	int count = 0;
	bool increase = true;

	float enemy_player_radius;
	float delta_y;
	float delta_x;
	float radius_deltax;

	SDL_Rect base;

	Direction dir;

public:

	EnemyRoundedTurret(int x, int y, ENEMY_TYPES type);

	void Draw();
	void Move();
	void Shot();
};

#endif 