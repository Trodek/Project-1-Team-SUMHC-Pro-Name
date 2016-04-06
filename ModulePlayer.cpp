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

	//Char Up anim
	up.PushBack({14,6,29,38});
	up.PushBack({ 51, 6, 27, 37 });
	up.PushBack({ 87, 6, 27, 37 });
	up.PushBack({ 122, 6, 26, 37 });
	up.PushBack({ 156, 6, 28, 37 });
	up.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	main_char_up_tex = App->textures->Load("Sprites/Main Char/Moving/Up/Up.png");
	bool ret = true;
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	Animation* current_animation = &up;

	if (App->input->keyboard[SDL_SCANCODE_F]==KEY_STATE::KEY_DOWN)
		App->particles->AddParticle(App->particles->basic_laser_p0, position.x, position.y);

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(main_char_up_tex, position.x, position.y, &r);
	
	return UPDATE_CONTINUE;
}