#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"
#include "ModuleAudio.h"

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	BIGTURRET,
	TRAIN,
	BLUEBASIC_TRAIN,
	FAT_ROBOT_TRAIN,
	GREENBASIC,
	SMALLTURRET,
	BOSS,
	ROOMBA,
	NOTBASIC,
	NOTBASICCOMMANDER,
	STRANGE_LARGE,
	ENERGY_BOX,
	ENERGY_PILL,
	CHANGE_BOX,
	CHANGE_PILL,
	MISSILE_THROWER,
	POWERUP,
	SHIELD, 
	EXTRA_BOMB,
	SPEED
};

struct SDL_Texture;
class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	Path* path;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, Path* path = nullptr);
	void DestroyEnemies();

private:

	void SpawnEnemy(const EnemyInfo& info);
	uint loot;

private:

	Mix_Chunk* enemy_hitted;
	Mix_Chunk* change_weapon;
	Mix_Chunk* pick_energy;
	Mix_Chunk* pick_speed;
	Mix_Chunk* expand_energy;
	EnemyInfo queue[MAX_ENEMIES];

public:
	Enemy* enemies[MAX_ENEMIES];
};

#endif // __ModuleEnemies_H__