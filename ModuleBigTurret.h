#ifndef __ModuleBigTurret_H__
#define __ModuleBigTurret_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Particle;
class ModuleParticles;
struct Collider;


class ModuleBigTurret : public Module
{
public:
	ModuleBigTurret();
	~ModuleBigTurret();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:
	iPoint position;
	bool dead = false;

	SDL_Texture* big_turret_tex = nullptr;
	SDL_Texture* big_turret_fire_tex = nullptr;

	Animation idle;
	Animation dead_fire;

	Animation* current_animation = nullptr;

	Particle* turret_bullet = nullptr;
	Particle* shoot_start = nullptr;

	Collider* big_turret_collider;

	uint now;

};

#endif