#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleDrawParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"

update_status ModuleDrawParticles::Update(){

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = App->particles->active[i];

		if (p == nullptr || p->drawit==AFTER_PLAYER)
			continue;

		if (p->Update() == false)
		{
			if (p->collider_box != nullptr)
				p->collider_box->to_delete = true;
			delete p;
			App->particles->active[i] = nullptr;


		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->BlitParticle(p->tex, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->angle);
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlaySoundEffect(p->sound);
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}