#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	basic_laser_tex = App->textures->Load("Sprites/Main Char/Weapons/basic laser.png");

	// laser particle
	basic_laser_p0.start_anim.PushBack({ 7, 6, 14, 16 });
	basic_laser_p0.start_anim.PushBack({ 7, 6, 14, 16 });
	basic_laser_p0.start_anim.loop = false;
	basic_laser_p0.start_anim.speed = 0.2f;
	basic_laser_p0.anim.PushBack({ 34, 6, 4, 16 });
	basic_laser_p0.anim.PushBack({ 34, 6, 4, 16 });
	basic_laser_p0.anim.loop = true;
	basic_laser_p0.anim.speed = 0.1f;
	basic_laser_p0.end_anim.PushBack({ 54, 6, 16, 16 });
	basic_laser_p0.end_anim.PushBack({ 74, 6, 16, 16 });
	basic_laser_p0.end_anim.PushBack({ 95, 11, 6, 6 });
	basic_laser_p0.end_anim.PushBack({ 108, 6, 14, 15 });
	basic_laser_p0.end_anim.loop = false;
	basic_laser_p0.end_anim.speed = 0.2f;
	basic_laser_p0.life = 800;
	basic_laser_p0.speed.y = -5;
	

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(basic_laser_tex);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
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

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			if (p->end_anim.Finished()){
				delete p;
				active[i] = nullptr;
			}
			else 
				App->render->BlitParticle(basic_laser_tex, p->position.x-6, p->position.y, &(p->end_anim.GetCurrentFrame()), p->angle);
		}
		else if(SDL_GetTicks() >= p->born)
		{
			if (!p->start_anim.Finished())
				App->render->BlitParticle(basic_laser_tex, p->start_pos.x, p->start_pos.y, &(p->start_anim.GetCurrentFrame()), p->angle);
			App->render->BlitParticle(basic_laser_tex, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->angle);
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, double angle, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	p->start_pos.x = x-5;
	p->start_pos.y = y;
	p->angle = angle;

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
start_anim(p.start_anim), anim(p.anim), end_anim(p.end_anim), position(p.position), start_pos(p.start_pos), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
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

	return ret;
}