#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Particle;
class ModuleParticles;

enum PlayerDirection{
	IDLE = -1, LEFT, ANGLE_60, LEFT_UP, ANGLE_30, UP, ANGLE_330,
	RIGHT_UP, ANGLE_300, RIGHT, ANGLE_240, RIGHT_DOWN,
	ANGLE_210, DOWN, ANGLE_150, LEFT_DOWN, ANGLE_120 
};

enum Weapons{
	LASER, MULTI, SUPERBALL, SUPERBURNER
};

enum Power{
	P0, P1, P2
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

	bool CheckPJAnimPos(Animation* anim, PlayerDirection dest_anim);
	void CreateShoot(Weapons equiped, Animation* anim)const;
	Weapons ChangeWeapon(Weapons current);
	Animation* SelectAnimation(PlayerDirection direction);

public:
	fPoint position;
	SDL_Texture* main_char_tex = nullptr;
	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation left_up;
	Animation left_down;
	Animation right_up;
	Animation right_down;
	Animation* current_animation = nullptr;
	Animation* weapon_anim = nullptr;
	Animation laser_360;

	Animation multi_up;
	Animation multi_down;
	Animation multi_left;
	Animation multi_right;
	Animation multi_360;

	Particle* laser_p0 = nullptr;
	Particle* laser_p1 = nullptr;
	Particle* laser_p2 = nullptr;
	Particle* shoot_start = nullptr;
	Particle* laser_end = nullptr;
	
	Particle* multi_laser_p0 = nullptr;
	Particle* multi_laser_p1 = nullptr;
	Particle* multi_laser_p2 = nullptr;
	Particle* multi_start = nullptr;
	Particle* multi_end = nullptr;

	PlayerDirection direction;
	Power current_power;
	Weapons current_weapon;
	Weapons last_basic_weapon;

};

#endif