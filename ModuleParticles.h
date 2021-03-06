#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_ACTIVE_PARTICLES 1500

enum DRAW{
	BEFOR_PLAYER, AFTER_PLAYER,
};

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
	DRAW drawit = AFTER_PLAYER;
	
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

	void DestroyParticles();

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, SDL_Rect collider_pos, double angle = 0, Uint32 delay = 0);
	void SetParticleSpeed(Particle* part, float x, float y);
	void SetColliderCorrection(Particle* part, uint x, uint y);

private:

	SDL_Texture* basic_laser_tex = nullptr;
	SDL_Texture* multi_laser_tex = nullptr;
	SDL_Texture* big_turret_bullet_tex = nullptr;
	SDL_Texture* truck_tex = nullptr;
	SDL_Texture* fat_robot_laser_tex = nullptr;
	SDL_Texture* fat_robot_laser_tex_inver = nullptr;
	uint last_particle = 0;

public:

	Particle* active[MAX_ACTIVE_PARTICLES];

	SDL_Texture* green_basic;
	SDL_Texture* blue_basic;
	SDL_Texture* small_turret;
	SDL_Texture* boss = nullptr;
	SDL_Texture* roomba = nullptr;
	SDL_Texture* notbasic = nullptr;
	SDL_Texture* strange_large = nullptr;;
	SDL_Texture* boxes;
	SDL_Texture* missilethrower;
	SDL_Texture* fat_robot_train;
	SDL_Texture* train;
	SDL_Texture* rounded_turret;
	SDL_Texture* notbasiccommander;
	SDL_Texture* notsobasicgreen;

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
	Particle truck_dead_hole;

	Particle green_basic_dead;
	Particle green_basic_bullet;
	Particle green_basic_bullet_end;
	Particle green_basic_bullet_start;

	Particle missile;
	Particle bannana;

	Particle missile2;

	Particle enemy_shot_especial;
	Particle enemy_blaster;

	Particle fat_robot_train_laser;
	Particle fat_robot_train_laser_end;
};

#endif // __MODULEPARTICLES_H__