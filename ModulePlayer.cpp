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

	/*//char idle up
	idle_up.PushBack({ 17, 273, 29, 38 });
	idle_up.speed = 0.1f;
	idle_up.loop = false;*/

	//Char Up anim
	up.PushBack({ 17, 273, 29, 38 });
	up.PushBack({ 55, 274, 27, 37 });
	up.PushBack({ 90, 274, 27, 37 });
	up.PushBack({ 126, 273, 26, 37 });
	up.PushBack({ 161, 274, 28, 37 });
	up.speed = 0.1f;

	/*//char up_to_right anim
	up_to_right.PushBack({ 18, 230, 27, 36 });
	up_to_right.speed = 0.1f;
	up_to_right.loop = false;*/

	//char right anim
	right.PushBack({ 94, 230, 27, 35 });
	right.PushBack({ 131, 230, 25, 36 });
	right.PushBack({ 166, 231, 28, 35 });
	right.PushBack({ 204, 230, 26, 37 });
	right.PushBack({ 55, 231, 29, 35 });
	right.speed = 0.1f;

	/*//char idle_right
	idle_right.PushBack({ 55, 231, 29, 35 });
	idle_right.speed = 0.1f;
	idle_right.loop = false;

	//char up_to_left
	up_to_left.PushBack({ 202, 190, 28, 36 });
	up_to_left.speed = 0.1f;
	up_to_left.loop = false;*/

	//char left
	left.PushBack({ 166, 191, 29, 35 });
	left.PushBack({ 131, 192, 28, 33 });
	left.PushBack({ 93, 191, 28, 35 });
	left.PushBack({ 55, 192, 29, 35 });
	left.PushBack({ 18, 191, 27, 35 });
	left.speed = 0.1f;

	/*//char idle_left
	idle_left.PushBack({ 55, 192, 29, 35 });
	idle_left.speed = 0.1f;
	idle_left.loop = false;*/

	//180�
	char_move_360.PushBack({ 55, 192, 29, 35 });  //-- left
	char_move_360.PushBack({ 202, 190, 28, 36 }); //-- left-up
	char_move_360.PushBack({ 17, 273, 29, 38 });  //-- up
	char_move_360.PushBack({ 18, 230, 27, 36 });  //-- right-up
	char_move_360.PushBack({ 55, 231, 29, 35 });  //-- right

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	main_char_tex = App->textures->Load("Sprites/Main Char/Main_moves.png");
	current_animation = &idle_up;
	bool ret = true;
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{


	int speed = 1;


	// Shoot key
	if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN){
		App->particles->AddParticle(App->particles->basic_laser_p0, position.x, position.y);
	}

	// W key
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
		current_animation = &up;
		position.y -= speed;
		direction = 2;
	}
	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP){
		current_animation = &idle_up;
	}

	// D key
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
		current_animation = &right;
		position.x += speed;
		direction = 4;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP){

		current_animation = &idle_right;	
	}

	// A key
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
		current_animation = &left;
		position.x -= speed;
		direction = 0;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP){
			current_animation = &idle_left;
	}
		
	if (CheckAnimPos(direction))
	App->render->Blit(main_char_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
	else App->render->Blit(main_char_tex, position.x, position.y, &char_move_360.GetCurrentFrame());

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CheckAnimPos(uint dest_anim){
	if (char_move_360.GetCurrentFrame().x == char_move_360.frames[dest_anim].x 
		&& char_move_360.GetCurrentFrame().y == char_move_360.frames[dest_anim].y) return true;
	else return false;
}