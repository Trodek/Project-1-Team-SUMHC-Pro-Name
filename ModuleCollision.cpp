 #include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"

ModuleCollision::ModuleCollision()
{
	player_collided = false;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_HOLE] = false;
	matrix[COLLIDER_WALL][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_WALL][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOMB] = false;
	matrix[COLLIDER_WALL][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOX] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_WALL][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_WALL][COLLIDER_SPEED] = false;
	matrix[COLLIDER_WALL][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_WALL][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_WALL][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_WALL][COLLIDER_DOOR] = false;

	matrix[COLLIDER_HOLE][COLLIDER_HOLE] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_HOLE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOLE][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_HOLE][COLLIDER_BOMB] = false;
	matrix[COLLIDER_HOLE][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_HOLE][COLLIDER_BOX] = false;
	matrix[COLLIDER_HOLE][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_HOLE][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_HOLE][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_HOLE][COLLIDER_SPEED] = false;
	matrix[COLLIDER_HOLE][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_HOLE][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_HOLE][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_HOLE][COLLIDER_DOOR] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOLE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOLE_BOSS_RIGHT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOLE_BOSS_LEFT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PASS_BULLET] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOX] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORMR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORML] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_SPEED] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DOOR] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOLE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PASS_BULLET] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_DEAD_EXPLO] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_SPEED] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_DOOR] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOX] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SPEED] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DOOR] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMB] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DEAD_EXPLO] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SPEED] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DOOR] = true;

	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_BOX] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_SPEED] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_DOOR] = false;

	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_BOX] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_SPEED] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_DOOR] = false;

	matrix[COLLIDER_PASS_BULLET][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_WALL] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_BOX] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_SPEED] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_DOOR] = false;

	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_BOX] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_ENERGY] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_CHANGE] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_POWERUP] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_SPEED] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_SHIELD] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_EXTRA_BOMB] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_EXTENDEDENERGY] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_DOOR] = false;

	matrix[COLLIDER_BOMB][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_BOMB][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_HOLE] = false;
	matrix[COLLIDER_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB] = false;
	matrix[COLLIDER_BOMB][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOX] = true;
	matrix[COLLIDER_BOMB][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_BOMB][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BOMB][COLLIDER_SPEED] = false;
	matrix[COLLIDER_BOMB][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_BOMB][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_BOMB][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_BOMB][COLLIDER_DOOR] = true;

	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_HOLE] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_WALL] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_BOMB] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_BOX] = true;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_SPEED] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_DEAD_EXPLO][COLLIDER_DOOR] = true;

	matrix[COLLIDER_BOX][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_BOX][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_BOX][COLLIDER_HOLE] = false;
	matrix[COLLIDER_BOX][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_BOX][COLLIDER_BOMB] = true;
	matrix[COLLIDER_BOX][COLLIDER_DEAD_EXPLO] = true;
	matrix[COLLIDER_BOX][COLLIDER_BOX] = false;
	matrix[COLLIDER_BOX][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_BOX][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BOX][COLLIDER_SPEED] = false;
	matrix[COLLIDER_BOX][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_BOX][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_BOX][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_BOX][COLLIDER_DOOR] = false;

	matrix[COLLIDER_ENERGY][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_HOLE] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_ENERGY][COLLIDER_BOMB] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_SPEED] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_ENERGY][COLLIDER_DOOR] = false;

	matrix[COLLIDER_POWERUP][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_HOLE] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_SPEED] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_DOOR] = false;

	matrix[COLLIDER_SPEED][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_SPEED][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_SPEED][COLLIDER_HOLE] = false;
	matrix[COLLIDER_SPEED][COLLIDER_WALL] = false;
	matrix[COLLIDER_SPEED][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_SPEED][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_SPEED][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_SPEED][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_SPEED][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_SPEED][COLLIDER_BOMB] = false;
	matrix[COLLIDER_SPEED][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_SPEED][COLLIDER_BOX] = false;
	matrix[COLLIDER_SPEED][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_SPEED][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_SPEED][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_SPEED][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_SPEED][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_SPEED][COLLIDER_SPEED] = false;
	matrix[COLLIDER_SPEED][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_SPEED][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_SPEED][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_SPEED][COLLIDER_DOOR] = false;

	matrix[COLLIDER_SHIELD][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_HOLE] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_WALL] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_SHIELD][COLLIDER_BOMB] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_BOX] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_SPEED] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_DOOR] = false;

	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_HOLE] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_BOMB] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_BOX] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_SPEED] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_EXTRA_BOMB][COLLIDER_DOOR] = false;


	matrix[COLLIDER_CHANGE][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_HOLE] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_WALL] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_CHANGE][COLLIDER_BOMB] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_BOX] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_SPEED] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_CHANGE][COLLIDER_DOOR] = false;

	matrix[COLLIDER_PLATFORMR][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLATFORMR][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_BOX] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_SPEED] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_PLATFORMR][COLLIDER_DOOR] = false;

	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_HOLE] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_WALL] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_BOMB] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_DEAD_EXPLO] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_BOX] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_SPEED] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_EXTENDEDENERGY][COLLIDER_DOOR] = false;

	matrix[COLLIDER_DOOR][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_DOOR][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_DOOR][COLLIDER_HOLE] = false;
	matrix[COLLIDER_DOOR][COLLIDER_WALL] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DOOR][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_DOOR][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_DOOR][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_DOOR][COLLIDER_BOMB] = true;
	matrix[COLLIDER_DOOR][COLLIDER_DEAD_EXPLO] = true;
	matrix[COLLIDER_DOOR][COLLIDER_BOX] = false;
	matrix[COLLIDER_DOOR][COLLIDER_ENERGY] = false;
	matrix[COLLIDER_DOOR][COLLIDER_CHANGE] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLATFORMR] = false;
	matrix[COLLIDER_DOOR][COLLIDER_PLATFORML] = false;
	matrix[COLLIDER_DOOR][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_DOOR][COLLIDER_SPEED] = false;
	matrix[COLLIDER_DOOR][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_DOOR][COLLIDER_EXTRA_BOMB] = false;
	matrix[COLLIDER_DOOR][COLLIDER_EXTENDEDENERGY] = false;
	matrix[COLLIDER_DOOR][COLLIDER_DOOR] = false;

	player_collisioning = 0;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				COLLIDER_TYPE c1_type = c1->type;
				if (matrix[c1->type][c2->type] && c1->callback){
					Direction dir = c1->ColliderHit(c2->rect);
					if (c1->type == COLLIDER_PLAYER || c1->type == COLLIDER_PLAYER_EBULLETS) {
						App->player->OnCollision(c1, c2, dir);
						switch (dir) {
						case UP:
							player_collisioning += 1;
							break;
						case LEFT:
							player_collisioning += 2;
							break;
						case RIGHT:
							player_collisioning += 4;
							break;
						case DOWN:
							player_collisioning += 7;
							break;
						}
					}
					else
						c1->callback->OnCollision(c1, c2);
					if (c2->type == COLLIDER_PLAYER_SHOT)
						c2->callback->OnCollision(c2, c1);
				}
				if (c1->type != c1_type) continue;	//Check if the c1 collider have changed befor continue

				if (matrix[c2->type][c1->type] && c2->callback) {
					Direction dir_2 = c2->ColliderHit(c1->rect);
					if (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_PLAYER_EBULLETS) {
						App->player->OnCollision(c2, c1, dir_2);
						player_collided = true;
					}
					else
						c2->callback->OnCollision(c2, c1);
				}
			}
		}	
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	DebugDraw();

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::PostUpdate()
{
	switch (player_collisioning) {
	case 0:								//no collision
		App->player->move_left = true;
		App->player->move_right = true;
		App->player->move_down = true;
		App->player->move_up = true;
		break;
	case 1:								//collision UP
		App->player->move_left = true;
		App->player->move_right = true;
		App->player->move_down = true;
		break;
	case 2:								//collision LEFT
		App->player->move_up = true;
		App->player->move_right = true;
		App->player->move_down = true;
		break;
	case 3:								//collision LEFT + UP
		App->player->move_down = true;
		App->player->move_right = true;
		break;
	case 4:								//collision RIGHT
		App->player->move_left = true;
		App->player->move_up = true;
		App->player->move_down = true;
		break;
	case 5:								//collision RIGHT + UP
		App->player->move_left = true;
		App->player->move_down = true;
		break;
	case 6:								//collision RIGHT + LEFT
		App->player->move_down = true;
		App->player->move_up = true;
		break;
	case 7:								//collision DOWN
		App->player->move_left = true;
		App->player->move_right = true;
		App->player->move_up = true;
		break;
	case 8:								//collision DOWN + UP
		App->player->move_left = true;
		App->player->move_right = true;
		break;
	case 9:								//collision DOWN + LEFT
		App->player->move_up = true;
		App->player->move_right = true;
		break;
	case 11:							//collision DOWN + RIGHT
		App->player->move_left = true;
		App->player->move_up = true;
		break;
	}
	player_collisioning = 0;

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if(App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if(debug == false)
		return;

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case COLLIDER_WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_ENEMY: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_PLAYER_SHOT: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case COLLIDER_ENEMY_SHOT: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case COLLIDER_HOLE: // brown
				App->render->DrawQuad(colliders[i]->rect, 205, 133, 63, alpha);
				break;
			case COLLIDER_HOLE_BOSS_RIGHT: // cyan
				App->render->DrawQuad(colliders[i]->rect, 176, 196, 222, alpha);
				break;
			case COLLIDER_HOLE_BOSS_LEFT: // cyan
				App->render->DrawQuad(colliders[i]->rect, 176, 196, 222, alpha);
				break;
			case COLLIDER_PASS_BULLET: // lime
				App->render->DrawQuad(colliders[i]->rect, 127, 201, 22, alpha);
				break;
			case COLLIDER_PLAYER_EBULLETS: // lavander
				App->render->DrawQuad(colliders[i]->rect, 228, 23, 197, alpha);
				break;
			case COLLIDER_BOMB: //purple?
				App->render->DrawQuad(colliders[i]->rect, 120, 20, 255, alpha);
				break;
			case COLLIDER_DEAD_EXPLO: //black
				App->render->DrawQuad(colliders[i]->rect, 200, 200, 255, alpha);
				break;
			case COLLIDER_BOX: 
				App->render->DrawQuad(colliders[i]->rect, 52, 20, 255, alpha);
				break;
			case COLLIDER_ENERGY: 
				App->render->DrawQuad(colliders[i]->rect, 20, 20, 25, alpha);
				break;
			case COLLIDER_CHANGE: 
				App->render->DrawQuad(colliders[i]->rect, 2, 200, 55, alpha);
				break;
			case COLLIDER_PLATFORMR:
				App->render->DrawQuad(colliders[i]->rect, 50, 150, 55, alpha);
				break;
			case COLLIDER_PLATFORML:
				App->render->DrawQuad(colliders[i]->rect, 50, 150, 55, alpha);
				break;
			case COLLIDER_DOOR:
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}

Direction Collider::ColliderHit(const SDL_Rect & r) const {
	
	if (rect.x >= r.x + r.w - App->player->speed) return LEFT;
	else if (rect.x + rect.w <= r.x + App->player->speed) return RIGHT;
	else if (rect.y >= r.y + r.h - App->player->speed) return UP;
	return DOWN;
}