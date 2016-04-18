#ifndef __ModuleGreenBasic_H__
#define __ModuleGreenBasic_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Particle;
class ModuleParticles;
struct Collider;


class ModuleGreenBasic : public Module
{
public:
	ModuleGreenBasic();
	~ModuleGreenBasic();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool CheckPJAnimPos(Animation* anim, Direction dest_anim);
	void CreateShoot(Animation* anim)const;
	Animation* SelectAnimation(Direction direction);
	void ResetPosition();
	void OnCollision(Collider* c1, Collider* c2);

public:
	iPoint position;
	iPoint PreviousPos;
	bool dead = false;

	SDL_Texture* basic_green_tex = nullptr;

	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation left_up;
	Animation left_down;
	Animation right_up;
	Animation right_down;
	Animation die;
	Animation move_360;

	Animation* current_animation = nullptr;
	Animation* weapon_anim = nullptr;

	Particle* laser_p0 = nullptr;
	Particle* shoot_start = nullptr;
	Particle* laser_end = nullptr;

	Direction direction;

	Collider* GreenBasicCollider;

	uint now;

};

#endif