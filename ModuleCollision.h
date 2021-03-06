#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 500

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_HOLE,
	COLLIDER_HOLE_BOSS_LEFT,
	COLLIDER_HOLE_BOSS_RIGHT,
	COLLIDER_PASS_BULLET,
	COLLIDER_PLAYER_EBULLETS,
	COLLIDER_BOMB,
	COLLIDER_DEAD_EXPLO,
	COLLIDER_BOX,
	COLLIDER_ENERGY,
	COLLIDER_CHANGE,
	COLLIDER_PLATFORMR,
	COLLIDER_PLATFORML,
	COLLIDER_POWERUP,
	COLLIDER_SPEED,
	COLLIDER_SHIELD,
	COLLIDER_EXTRA_BOMB,
	COLLIDER_EXTENDEDENERGY,
	COLLIDER_DOOR,




	COLLIDER_MAX,
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	Direction ColliderHit(const SDL_Rect& r) const;
	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();


private:

	int player_collisioning;
	bool player_collided;
	Collider* colliders[MAX_COLLIDERS];
	bool debug = false;

public:
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
};

#endif // __ModuleCollision_H__