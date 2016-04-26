#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "EnemySmallTurret.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "Enemy.h"
#include "EnemyBigTurret.h"
#include "EnemyTruck.h"
#include "EnemyGreenBasic.h"
#include "ModuleBomb.h"

#define SPAWN_MARGIN 150

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}


update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].y * SCREEN_SIZE > -App->render->camera.y - SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Move();
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->UpdateAnim();
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw();
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Shot();

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if (enemies[i]->position.y* SCREEN_SIZE >(-App->render->camera.y + 960) + SPAWN_MARGIN || enemies[i]->position.x > 240 || enemies[i]->position.x < -SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y,Path* path)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].path = path;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::BIGTURRET:
				enemies[i] = new EnemyBigTurret(info.x,info.y,info.type);
				break;
			case ENEMY_TYPES::TRUCK:
				enemies[i] = new EnemyTruck(info.x, info.y,info.type);
				break;
			case ENEMY_TYPES::GREENBASIC:
				enemies[i] = new EnemyGreenBasic(info.x, info.y, info.type);
				enemies[i]->SetPath(info.path);
				break;
			case ENEMY_TYPES::SMALLTURRET:
				enemies[i] = new EnemySmallTurret(info.x, info.y, info.type);
				break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{	
			if (c2->type == COLLIDER_PLAYER_SHOT && enemies[i]->hp>0){
				enemies[i]->hp -= App->player->GetDmg();
				if (enemies[i]->hp < 1){
					if (enemies[i]->type == TRUCK) App->particles->AddParticle(App->particles->truck_dead_hole, enemies[i]->position.x + 1, enemies[i]->position.y-126, COLLIDER_NONE, { 0, 0, 0, 0 }, 0);
					App->particles->AddParticle(*enemies[i]->dead, enemies[i]->position.x, enemies[i]->position.y+enemies[i]->y_collider_correction, COLLIDER_NONE, { 0, 0, 0, 0 });
					App->ui->score += enemies[i]->points;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if (c2->type == COLLIDER_BOMB && enemies[i]->hp>0){
				enemies[i]->hp -= 125;
				if (enemies[i]->hp < 1){
					if (enemies[i]->type == TRUCK) App->particles->AddParticle(App->particles->truck_dead_hole, enemies[i]->position.x + 1, enemies[i]->position.y - 126, COLLIDER_NONE, { 0, 0, 0, 0 }, 0);
					App->particles->AddParticle(*enemies[i]->dead, enemies[i]->position.x, enemies[i]->position.y + enemies[i]->y_collider_correction, COLLIDER_NONE, { 0, 0, 0, 0 });
					App->ui->score += enemies[i]->points;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			break;
		}
	}
}