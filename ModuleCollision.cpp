 #include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_HOLE] = false;
	matrix[COLLIDER_WALL][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_WALL][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOMB] = false;

	matrix[COLLIDER_HOLE][COLLIDER_HOLE] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_HOLE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOLE][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_HOLE][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_HOLE][COLLIDER_BOMB] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOLE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOLE_BOSS_RIGHT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOLE_BOSS_LEFT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PASS_BULLET] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOLE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PASS_BULLET] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_EBULLETS] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMB] = true;

	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_HOLE_BOSS_RIGHT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_HOLE_BOSS_RIGHT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_HOLE] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_HOLE_BOSS_LEFT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_PASS_BULLET][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_WALL] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PASS_BULLET][COLLIDER_BOMB] = false;

	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_HOLE] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_PLAYER_EBULLETS][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMB][COLLIDER_PASS_BULLET] = false;
	matrix[COLLIDER_BOMB][COLLIDER_HOLE_BOSS_LEFT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_HOLE] = false;
	matrix[COLLIDER_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_EBULLETS] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->CheckCollision(c2->rect) == true)
			{
				if(matrix[c1->type][c2->type] && c1->callback) 
					c1->callback->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->callback) 
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if(App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if(debug == false)
		return;

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case COLLIDER_HOLE: // brown
			App->render->DrawQuad(colliders[i]->rect, 205, 133, 63, alpha);
			break;
			case COLLIDER_HOLE_BOSS_RIGHT: // cyan
			App->render->DrawQuad(colliders[i]->rect, 176, 196, 222, alpha);
			break;
			case COLLIDER_HOLE_BOSS_LEFT: // cyan
			App->render->DrawQuad(colliders[i]->rect, 176, 196, 222, alpha);
			break;
			case COLLIDER_PASS_BULLET: // lime
			App->render->DrawQuad(colliders[i]->rect, 127, 201, 22, alpha);
			break;
			case COLLIDER_PLAYER_EBULLETS: // lavander
			App->render->DrawQuad(colliders[i]->rect, 228, 23, 197, alpha);
			break;
			case COLLIDER_BOMB: //black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}