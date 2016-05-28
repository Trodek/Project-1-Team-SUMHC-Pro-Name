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
	TRUCK,
	GREENBASIC,
	SMALLTURRET,
	BOSS,
	ROOMBA,
	STRANGE_LARGE,
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

private:

	Mix_Chunk* enemy_hitted;
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
};

#endif // __ModuleEnemies_H__