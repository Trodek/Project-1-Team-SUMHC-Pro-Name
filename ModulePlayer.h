#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Particle;
class ModuleParticles;
struct Collider;


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
	update_status PostUpdate();
	bool CleanUp();


	bool CheckPJAnimPos(Animation* anim, Direction dest_anim, char player);
	void CreateShoot(Weapons equiped, Animation* anim, iPoint position)const;
	Weapons ChangeWeapon(Weapons current, char player);
	void SelectAnimation(Direction direction, char player, Weapons current_weapon);
	void ResetPosition();
	void OnCollision(Collider* c1, Collider* c2, Direction dir);

	//bool CheckColliders();

	int GetDmg();

public:
	iPoint position;
	iPoint PreviousPos;

	iPoint position_p2;
	iPoint PreviousPos_p2;


	bool dead = false;
	bool dead_p2 = false;
	bool dead_fall = false;
	bool dead_fall_p2 = false;
	bool pos_changed = false;
	bool pos_changed_2 = false;

	SDL_Texture* main_char_tex = nullptr;
	SDL_Texture* bomb_tex = nullptr;
	SDL_Texture* dead_explo_text = nullptr;
	SDL_Texture* casual_tex = nullptr;

	SDL_Rect casual;

	//SDL_Rect Playeraux;

	bool move_up, move_down, move_left, move_right, god_mode = false;
	bool move_up_p2, move_down_p2, move_left_p2, move_right_p2;

	Animation up;
	Animation up_p2;
	Animation down;
	Animation down_p2;
	Animation left;
	Animation left_p2;
	Animation right;
	Animation right_p2;
	Animation left_up;
	Animation left_up_p2;
	Animation left_down;
	Animation left_down_p2;
	Animation right_up;
	Animation right_up_p2;
	Animation right_down;
	Animation right_down_p2;
	Animation fall_hole;
	Animation fall_hole_p2;
	Animation laser_360;
	Animation laser_360_p2;
	Animation bomb;
	Animation dead_explo;
	Animation dead_explo_p2;

	Animation multi_up;
	Animation multi_down;
	Animation multi_left;
	Animation multi_right;
	Animation multi_360;

	Animation multi_up_p2;
	Animation multi_down_p2;
	Animation multi_left_p2;
	Animation multi_right_p2;
	Animation multi_360_p2;

	Animation* current_animation = nullptr;
	Animation* player2_current_animation = nullptr;
	Animation* weapon_anim = nullptr;
	Animation* weapon_anim_player2 = nullptr;

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

	Direction direction;
	Direction direction_p2;
	Power current_power;
	Power current_power_player2;
	Weapons current_weapon;
	Weapons current_weapon_player2;
	Weapons last_basic_weapon;
	Weapons last_basic_weapon_player2;

	Collider* PlayerCollider;
	Collider* PlayerEBulletsCollider;
	Collider* Player_explosion;
	Collider* Player2_explosion;

	Collider* Player2Collider;
	Collider* Player2EBulltesCollider;

	bool bomb_pressed;
	bool collider_create = false;
	uint last_laser;
	uint last_laser_p2;
	uint last_multi;
	uint last_multi_p2;
	uint now;



};

#endif