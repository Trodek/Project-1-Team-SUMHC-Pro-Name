#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"


ModulePlayer::ModulePlayer()
{
	position.x = 120;
	position.y = 245;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	
	bool ret = true;
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_F]==KEY_STATE::KEY_DOWN)
		App->particles->AddParticle(App->particles->basic_laser_p0, position.x, position.y);
	
	return UPDATE_CONTINUE;
}