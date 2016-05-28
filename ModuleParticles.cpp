#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

#define nullrect {0,0,0,0} 

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) 
		active[i] = nullptr;

	//enemy_shot_especial

	enemy_shot_especial.anim.PushBack({ 10, 60, 14, 15 });
	enemy_shot_especial.anim.PushBack({ 35, 60, 14, 15 });
	enemy_shot_especial.anim.speed = 0.5f;
	enemy_shot_especial.life = 1500;
	enemy_shot_especial.collider = COLLIDER_ENEMY_SHOT;
	enemy_shot_especial.end_particle = &green_basic_bullet_end;

	//enemy_blaster

	enemy_blaster.anim.PushBack({ 80, 48, 8, 40 });
	enemy_blaster.life = 1500;
	enemy_blaster.speed.y = 2;
	enemy_blaster.drawit = BEFOR_PLAYER;
	enemy_blaster.end_particle = &green_basic_bullet_end;

	//missile paritcle

	missile.anim.PushBack({ 46, 197, 16, 64});
	missile.anim.PushBack({ 73, 197, 16, 64 });
	missile.anim.PushBack({ 100, 197, 16, 64 });
	missile.anim.PushBack({ 126, 197, 16, 64 });
	missile.end_particle = &green_basic_dead;
	missile.life = 2000;
	missile.collider = COLLIDER_ENEMY_SHOT;
	missile.anim.speed = 1.1f;
	missile.anim.loop = true;
	missile.speed.y = 2;
	missile.drawit = BEFOR_PLAYER;
	missile.end_particle = &bannana;

	//banana particle
	
	bannana.anim.PushBack({ 177, 253, 16, 16 });
	bannana.anim.PushBack({ 202, 253, 16, 16 });
	bannana.anim.PushBack({ 223, 253, 16, 16 });
	bannana.anim.PushBack({ 246, 253, 16, 16 });
	bannana.anim.speed = 0.5f;
	bannana.life = 1500;
	bannana.collider = COLLIDER_ENEMY_SHOT;
	bannana.anim.loop = true;


	// laser particles and sound

	basic_laser_p0.anim.PushBack({ 34, 6, 4, 16 });
	basic_laser_p0.anim.loop = true;
	basic_laser_p0.anim.speed = 0.1f;
	basic_laser_p0.life = 1000;
	basic_laser_p0.end_particle = &laser_end;
	basic_laser_p0.collider = COLLIDER_PLAYER_SHOT;

	basic_laser_p1.anim.PushBack({ 32, 35, 10, 16 });
	basic_laser_p1.anim.loop = true;
	basic_laser_p1.anim.speed = 0.1f;
	basic_laser_p1.life = 1000;
	basic_laser_p1.end_particle = &laser_end;
	basic_laser_p1.collider = COLLIDER_PLAYER_SHOT;

	basic_laser_p2.anim.PushBack({ 26, 64, 24, 24 });
	basic_laser_p2.anim.loop = true;
	basic_laser_p2.anim.speed = 0.1f;
	basic_laser_p2.life = 1000;
	basic_laser_p2.end_particle = &laser_end;
	basic_laser_p2.collider = COLLIDER_PLAYER_SHOT;

	shoot_start.anim.PushBack({ 7, 6, 14, 16 });
	shoot_start.anim.loop = false;
	shoot_start.anim.speed = 1.0f;
	shoot_start.collider = COLLIDER_NONE;

	laser_end.anim.PushBack({ 54, 6, 16, 16 });
	laser_end.anim.PushBack({ 74, 6, 16, 16 });
	laser_end.anim.PushBack({ 95, 11, 6, 6 });
	laser_end.anim.PushBack({ 108, 6, 14, 15 });
	laser_end.anim.loop = false;
	laser_end.anim.speed = 0.2f;
	laser_end.collider = COLLIDER_NONE;

	// multi laser particles and sound

	multi_laser_p0.anim.PushBack({ 24, 38, 6, 14 });
	multi_laser_p0.anim.loop = true;
	multi_laser_p0.life = 1000;
	multi_laser_p0.end_particle = &multi_end;
	multi_laser_p0.collider = COLLIDER_PLAYER_SHOT;

	multi_laser_p1.anim.PushBack({ 52, 35, 10, 18 });
	multi_laser_p1.anim.loop = true;
	multi_laser_p1.life = 1000;
	multi_laser_p1.end_particle = &multi_end;
	multi_laser_p1.collider = COLLIDER_PLAYER_SHOT;

	multi_laser_p2.anim.PushBack({ 86, 32, 14, 21 });
	multi_laser_p2.anim.loop = true;
	multi_laser_p2.life = 1000;
	multi_laser_p2.end_particle = &multi_end;
	multi_laser_p2.collider = COLLIDER_PLAYER_SHOT;

	multi_start.anim.PushBack({ 39, 66, 36, 16 });
	multi_start.anim.loop = false;
	multi_start.anim.speed = 1.0f;

	multi_start.collider = COLLIDER_NONE;


	multi_end.anim.PushBack({ 11, 5, 16, 16 });
	multi_end.anim.PushBack({ 38, 5, 16, 15 });
	multi_end.anim.PushBack({ 75, 5, 10, 12 });
	multi_end.anim.PushBack({ 100, 5, 15, 13 });
	multi_end.anim.loop = false;
	multi_end.anim.speed = 0.3f;
	multi_end.collider = COLLIDER_NONE;

	//big turret bullet particles
	big_turret_bullet.anim.PushBack({ 43, 107, 14, 14 });
	big_turret_bullet.anim.PushBack({ 66, 106, 14, 14 });
	big_turret_bullet.anim.loop = true;
	big_turret_bullet.anim.speed = 0.3f;
	big_turret_bullet.life = 1000;
	big_turret_bullet.collider = COLLIDER_ENEMY_SHOT;
	big_turret_bullet.end_particle = nullptr;

	big_turret_bullet_start.anim.PushBack({ 4, 98, 30, 31 });
	big_turret_bullet_start.anim.loop = false;
	big_turret_bullet_start.anim.speed = 0.3f;
	big_turret_bullet_start.collider = COLLIDER_NONE;

	big_turret_dead.anim.PushBack({ 0, 0, 64, 65 });
	big_turret_dead.anim.PushBack({ 64, 0, 64, 65 });
	big_turret_dead.anim.PushBack({ 128, 0, 64, 65 });
	big_turret_dead.anim.PushBack({ 192, 0, 64, 65 });
	big_turret_dead.anim.PushBack({ 256, 0, 64, 65 });
	big_turret_dead.anim.speed = 0.2f;
	big_turret_dead.anim.loop = true;
	big_turret_dead.collider = COLLIDER_NONE;
	big_turret_dead.life = 50000;

	truck_footprint.anim.PushBack({ 167, 6, 66, 24 });

	truck_footprint.collider = COLLIDER_NONE;
	truck_footprint.life = 50000;
	truck_footprint.drawit = BEFOR_PLAYER;

	truck_dead.anim.PushBack({ 0, 0, 112, 168 });
	truck_dead.anim.PushBack({ 112, 0, 112, 168 });
	truck_dead.anim.PushBack({ 224, 0, 112, 168 });
	truck_dead.anim.PushBack({ 336, 0, 112, 168 });
	truck_dead.anim.PushBack({ 448, 0, 112, 168 });
	truck_dead.anim.PushBack({ 0, 168, 112, 168 });
	truck_dead.anim.PushBack({ 112, 168, 112, 168 });
	truck_dead.anim.PushBack({ 224, 168, 112, 168 });
	truck_dead.anim.PushBack({ 336, 168, 112, 168 });
	truck_dead.anim.PushBack({ 448, 168, 112, 168 });
	truck_dead.anim.PushBack({ 0, 336, 112, 168 });
	truck_dead.anim.PushBack({ 112, 336, 112, 168 });
	truck_dead.anim.PushBack({ 224, 336, 112, 168 });
	truck_dead.anim.PushBack({ 336, 336, 112, 168 });
	truck_dead.anim.PushBack({ 448, 336, 112, 168 });
	truck_dead.anim.PushBack({ 0, 504, 112, 168 });
	truck_dead.anim.PushBack({ 112, 504, 112, 168 });
	truck_dead.anim.PushBack({ 224, 504, 112, 168 });
	truck_dead.anim.PushBack({ 336, 504, 112, 168 });
	truck_dead.anim.PushBack({ 448, 504, 112, 168 });
	truck_dead.anim.PushBack({ 0, 672, 112, 168 });
	truck_dead.anim.PushBack({ 112, 672, 112, 168 });
	truck_dead.anim.PushBack({ 224, 672, 112, 168 });
	truck_dead.anim.PushBack({ 336, 672, 112, 168 });
	truck_dead.anim.PushBack({ 448, 672, 112, 168 });
	truck_dead.anim.speed = 0.3f;
	truck_dead.anim.loop = false;
	truck_dead.collider = COLLIDER_NONE;


	truck_dead_hole.anim.PushBack({ 480, 65, 96, 126 });

	truck_dead_hole.collider = COLLIDER_NONE;
	truck_dead_hole.life = 50000;
	truck_dead_hole.drawit = BEFOR_PLAYER;

	// green basic die
	green_basic_dead.anim.PushBack({ 0, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 44, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 88, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 132, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 176, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 220, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 264, 0, 44, 46 });
	green_basic_dead.anim.PushBack({ 308, 0, 44, 46 });
	green_basic_dead.anim.speed = 0.2f;
	green_basic_dead.anim.loop = false;
	green_basic_dead.collider = COLLIDER_NONE;


	green_basic_bullet.anim.PushBack({ 98, 235, 6, 6 });
	green_basic_bullet.anim.PushBack({ 113, 235, 6, 6 });
	green_basic_bullet.anim.speed = 0.3f;
	green_basic_bullet.end_particle = &green_basic_bullet_end;
	green_basic_bullet.life = 2500;

	green_basic_bullet.collider = COLLIDER_ENEMY_SHOT;

	green_basic_bullet_end.anim.PushBack({ 134, 234, 8, 8 });
	green_basic_bullet_end.anim.PushBack({ 151, 234, 8, 8 });
	green_basic_bullet_end.anim.PushBack({ 168, 235, 6, 5 });
	green_basic_bullet_end.anim.speed = 0.3f;
	green_basic_bullet_end.anim.loop = false;
	green_basic_bullet_end.collider = COLLIDER_NONE;


	green_basic_bullet_start.anim.PushBack({ 73, 230, 16, 16 });
	green_basic_bullet_start.anim.loop = false;
	green_basic_bullet_start.anim.speed = 0.3f;
	green_basic_bullet_start.collider = COLLIDER_NONE;

	
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	green_basic_dead.sound = App->audio->LoadSoundEffect("OutZone/Sounds/Effects/enemy die.wav");
	truck_dead.sound = App->audio->LoadSoundEffect("OutZone/Sounds/Effects/big enemy die.wav");

	multi_laser_tex = App->textures->Load("OutZone/Sprites/Main Char/Weapons/multi laser.png");
	truck_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Truck/Truck.png");
	small_turret = App->textures->Load("Outzone/Sprites/Enemies/Level 1/Small Turret/Small Turret.png");
	big_turret_dead.tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Big Turret/big turret fire.png");
	green_basic_dead.tex = App->textures->Load("OutZone/Sprites/Enemies/Enemies Common Dead/common dead sprites.png");
	boss = App->textures->Load("OutZone/Sprites/Enemies/Level 4/boss.png");
	roomba = App->textures->Load("OutZone/Sprites/Enemies/Level 4/roomba.png");
	notbasic = App->textures->Load("OutZone/Sprites/Enemies/Level 4/notsobasic.png");
	strange_large = App->textures->Load("OutZone/Sprites/Enemies/Level 4/StrangeLargeShit.png");

	enemy_blaster.tex = strange_large;
	enemy_shot_especial.tex = strange_large;

	missile.tex = boss;
	bannana.tex = boss;

	green_basic = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Green Soldier/Soldier Green.png");
	green_basic_bullet_start.tex = green_basic;
	green_basic_bullet.tex = green_basic;	
	green_basic_bullet_end.tex = green_basic;

	blue_basic = App->textures->Load("OutZone/Sprites/Enemies/Level 4/train/blue_static_soldier.png");

	truck_dead.tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Truck/Truck Explosion.png");
	truck_dead_hole.tex = truck_tex;	
	truck_footprint.tex = truck_tex;	

	big_turret_bullet_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Big Turret/big turret.png");
	big_turret_bullet_start.tex = big_turret_bullet_tex;	
	big_turret_bullet.tex = big_turret_bullet_tex;

	multi_start.sound = App->audio->LoadSoundEffect("OutZone/Sounds/Effects/3-gun shoot.wav");
	multi_start.tex = multi_laser_tex;
	multi_laser_p0.tex = multi_laser_tex;
	multi_laser_p1.tex = multi_laser_tex;
	multi_laser_p2.tex = multi_laser_tex;
	multi_end.tex = multi_laser_tex;

	basic_laser_tex = App->textures->Load("OutZone/Sprites/Main Char/Weapons/basic laser.png");
	laser_end.tex = basic_laser_tex;
	basic_laser_p0.tex = basic_laser_tex;	
	basic_laser_p1.tex = basic_laser_tex;	
	basic_laser_p2.tex = basic_laser_tex;

	shoot_start.sound = App->audio->LoadSoundEffect("OutZone/Sounds/Effects/basic_laser_shoot.wav");
	shoot_start.tex = basic_laser_tex;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(basic_laser_tex);
	App->textures->Unload(multi_laser_tex);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			App->audio->UnloadSoundEffect(active[i]->sound);
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr||p->drawit == BEFOR_PLAYER)
			continue;
			
		if(p->Update() == false)
		{
			if (p->collider_box != nullptr)
				p->collider_box->to_delete = true;
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->BlitParticle(p->tex, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->angle);
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlaySoundEffect(p->sound);
				// Play particle fx here
			}
		}
	}
	
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, SDL_Rect collider_size, double angle, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->angle = angle;
			if (collider_type != COLLIDER_NONE)
				p->collider_box = App->collisions->AddCollider(collider_size, collider_type, this);
			active[i] = p;
			break;
		}
	}

}

void ModuleParticles::SetParticleSpeed(Particle* part, float x, float y){

	part->speed.x = x;
	part->speed.y = y;
}

void ModuleParticles::SetColliderCorrection(Particle* part, uint x, uint y){
	part->collider_correction.x = x;
	part->collider_correction.y = y;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider_box == c1)
		{
			if (active[i]->end_particle != nullptr){
				if (active[i]->end_particle!=&bannana)
				AddParticle(*active[i]->end_particle, active[i]->position.x - 5, active[i]->position.y, COLLIDER_NONE, nullrect);
				else{
					SetParticleSpeed(&bannana, 0, -2);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, 1.41f, -1.41f);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, 2, 0);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, 1.41f, 1.41f);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, 0, 2);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, -1.41f, 1.41f);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, -2, 0);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
					SetParticleSpeed(&bannana, -1.41f, -1.41f);
					AddParticle(*active[i]->end_particle, active[i]->position.x + 5, active[i]->position.y, COLLIDER_ENEMY_SHOT, nullrect);
				}
			}
			active[i]->collider_box->to_delete = true;
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
//                          Particle
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed), angle(p.angle), tex(p.tex), end_particle(p.end_particle),
	fx(p.fx), born(p.born), life(p.life), sound(p.sound), collider(p.collider), collider_box(p.collider_box),
	fx_played(p.fx_played), collider_correction(p.collider_correction), drawit(p.drawit)
{}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;
	if ((SDL_GetTicks() - born) < life){
			position.x += speed.x;
			position.y += speed.y;
	}

	if (collider_box != nullptr)
		collider_box->SetPos(position.x+collider_correction.x, position.y+collider_correction.y);

	return ret;
}

