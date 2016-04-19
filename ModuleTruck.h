#ifndef __ModuleTruck_H__
#define __ModuleTruck_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Particle;
class ModuleParticles;
struct Collider;


class ModuleTruck : public Module
{
public:
	ModuleTruck();
	~ModuleTruck();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:
	iPoint position;
	bool dead = false;

	SDL_Texture* truck_tex = nullptr;

	Animation run;
	
	Animation* current_animation = nullptr;

	Collider* truck_collider;

	uint now;

};

#endif