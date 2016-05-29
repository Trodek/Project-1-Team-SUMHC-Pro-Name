#ifndef _Roomba_
#define _Roomba_

#include "Enemy.h"

enum ROOMBA_STATES {
	ST_RoombaIdle, ST_Fire,
};

class EnemyRoomba : public Enemy{
private:
	Animation Idle;
	Animation Fire;
	Animation Fire_end;

	bool change_state;

	ROOMBA_STATES curr_state = ST_RoombaIdle;

	uint cont;

	float enemy_player_radius;
	float delta_y;
	float delta_x;
	float angle;

	float speed = 1.2f;

	Particle* bullet;

	iPoint original;

public:
	EnemyRoomba(int x, int y, ENEMY_TYPES type);

	void Shot();
	void Move();
	void Draw(){}

	void CreateShots();

};

#endif