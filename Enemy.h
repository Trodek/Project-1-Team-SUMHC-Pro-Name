#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation;
	Collider* collider;
	SDL_Texture* tex;

public:
	iPoint position;
	Particle* dead;
	int hp;
	int points;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw();
	virtual void Shot(){};
	virtual void UpdateAnim(){};
};

#endif // __ENEMY_H__