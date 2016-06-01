#ifndef __Enemy_Train__
#define __Enemy_Train__

#include "Enemy.h"
#include "Globals.h"
#include "ModuleEnemies.h"

class EnemyTrain : public Enemy
{
private:

	iPoint original;
	Animation machine_top_anim;
	Animation door_idle_anim;
	Animation door_open_anim;
	Animation turret_idle_anim;
	Animation turret_shot_anim;

	Animation* current_anim;

	Particle* bullet;
	Particle* shoot_start;

	Direction dir = IDLE;

	int now;
	int last_shot;
	int open_door;
	bool shot_finish = true;
	bool start_spam = false;

	float enemy_player_radius;
	float delta_y;
	float delta_x;
	float radius_deltax;

public:

	EnemyTrain(int x, int y, ENEMY_TYPES type);

	void Shot();
	void Move();
	void Draw();
};

#endif // 