#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct SDL_Rect;

struct Particle
{
	Animation start_anim;
	Animation anim;
	Animation end_anim;
	uint fx = 0;
	iPoint position;
	iPoint start_pos;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	SDL_Rect crearion;
	
	bool fx_played = false;
	double angle;

	Particle();
	Particle(const Particle& p);
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y,double angle = 0 ,Uint32 delay = 0);

private:

	SDL_Texture* basic_laser_tex = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	Particle basic_laser_p0;

};

#endif // __MODULEPARTICLES_H__