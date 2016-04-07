#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
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
	multi_laser_tex = App->textures->Load("Sprites/Main Char/Weapons/multi laser.png");

	// laser particles and sound
	
	basic_laser_p0.anim.PushBack({ 34, 6, 4, 16 });
	basic_laser_p0.anim.loop = true;
	basic_laser_p0.anim.speed = 0.1f;
	basic_laser_p0.life = 1000;
	basic_laser_p0.tex = basic_laser_tex;

	shoot_start.anim.PushBack({ 7, 6, 14, 16 });
	shoot_start.anim.loop = false;
	shoot_start.anim.speed = 0.2f;
	shoot_start.sound = App->audio->LoadSoundEffect("Sounds/Effects/basic_laser_shoot.wav");
	shoot_start.tex = basic_laser_tex;

	laser_end.anim.PushBack({ 54, 6, 16, 16 });
	laser_end.anim.PushBack({ 74, 6, 16, 16 });
	laser_end.anim.PushBack({ 95, 11, 6, 6 });
	laser_end.anim.PushBack({ 108, 6, 14, 15 });
	laser_end.anim.loop = false;
	laser_end.anim.speed = 0.2f;
	laser_end.tex = basic_laser_tex;

	// multi laser particles and sound

	multi_laser_p0.anim.PushBack({ 24, 38, 6, 14 });
	multi_laser_p0.anim.loop = true;
	multi_laser_p0.life = 1000;
	multi_laser_p0.tex = multi_laser_tex;

	multi_start.anim.PushBack({ 39, 66, 36, 16 });
	multi_start.anim.loop = false;
	multi_start.anim.speed = 0.3f;
	multi_start.sound = App->audio->LoadSoundEffect("Sounds/Effects/3-gun shoot.wav");
	multi_start.tex = multi_laser_tex;

	multi_end.anim.PushBack({ 11, 5, 16, 16 });
	multi_end.anim.PushBack({ 38, 5, 16, 15 });
	multi_end.anim.PushBack({ 75, 5, 10, 12 });
	multi_end.anim.PushBack({ 100, 5, 15, 13 });
	multi_end.anim.loop = false;
	multi_end.anim.speed = 0.3f;
	multi_end.tex = multi_laser_tex;

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

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, double angle, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
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
 anim(p.anim), position(p.position), start_pos(p.start_pos), speed(p.speed),
 fx(p.fx), born(p.born), life(p.life), sound(p.sound), angle(p.angle), tex(p.tex)
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

void ModuleParticles::SetParticleSpeed(Particle* part, float x, float y){

	part->speed.x = x;
	part->speed.y = y;
}