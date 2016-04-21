#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	COLLIDER_TYPE collider;
	Collider* collider_box = nullptr;
	iPoint collider_correction;
	Animation anim;
	uint fx = 0;
	iPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	Mix_Chunk* sound = nullptr;
	SDL_Texture* tex = nullptr;
	Particle* end_particle = nullptr;
	
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
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, SDL_Rect collider_pos, double angle = 0, Uint32 delay = 0);
	void SetParticleSpeed(Particle* part, float x, float y);
	void SetColliderCorrection(Particle* part, uint x, uint y);

private:

	SDL_Texture* basic_laser_tex = nullptr;
	SDL_Texture* multi_laser_tex = nullptr;
	SDL_Texture* big_turret_bullet_tex = nullptr;
	SDL_Texture* truck_tex = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	Particle basic_laser_p0;
	Particle basic_laser_p1;
	Particle basic_laser_p2;
	Particle shoot_start;
	Particle laser_end;

	Particle multi_laser_p0;
	Particle multi_laser_p1;
	Particle multi_laser_p2;
	Particle multi_start;
	Particle multi_end;
	
	Particle big_turret_bullet;
	Particle big_turret_bullet_start;
	Particle big_turret_dead;

	Particle truck_footprint;
	Particle truck_dead;
};

#endif // __MODULEPARTICLES_H__