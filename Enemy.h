#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

struct SDL_Texture;
struct Collider;

enum Draw_Me{
	PILL,
	BEFORE,
	AFTER
};

class Enemy
{
protected:
	Animation* animation;
	Collider* collider;
	SDL_Texture* tex;
	Path* path;

	

public:
	int x_collider_correction = 0;
	int y_collider_correction = 0;
	ENEMY_TYPES type;
	iPoint position;
	Particle* dead = nullptr;
	int hp;
	int points;
	Draw_Me draw = AFTER;

public:
	Enemy(int x, int y, ENEMY_TYPES type);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw();
	virtual void Shot(){};
	virtual void UpdateAnim(){};
	void SetPath(Path* mov);
};

#endif // __ENEMY_H__