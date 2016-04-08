#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleSceneLevels.h"

ModulePlayer::ModulePlayer()
{
	position.x = 120;
	position.y = 245;

	//// LASER ANIMATIONS

	//Char Up anim
	up.PushBack({ 17, 273, 29, 38 });
	up.PushBack({ 55, 274, 27, 37 });
	up.PushBack({ 90, 274, 27, 37 });
	up.PushBack({ 126, 273, 26, 37 });
	up.PushBack({ 161, 274, 28, 37 });
	up.speed = 0.2f;

	//char right
	right.PushBack({ 92, 230, 28, 35 });
	right.PushBack({ 128, 230, 27, 36 });
	right.PushBack({ 165, 231, 30, 35 });
	right.PushBack({ 202, 230, 28, 37 });
	right.PushBack({ 55, 231, 29, 35 });
	right.speed = 0.25f;

	//char left
	left.PushBack({ 166, 191, 29, 35 });
	left.PushBack({ 131, 192, 28, 33 });
	left.PushBack({ 93, 191, 28, 35 });
	left.PushBack({ 55, 192, 29, 35 });
	left.PushBack({ 18, 191, 27, 35 });
	left.speed = 0.25f;

	//char down
	down.PushBack({ 54, 139, 31, 39 });
	down.PushBack({ 92, 141, 28, 39 });
	down.PushBack({ 125, 143, 27, 37 });
	down.PushBack({ 156, 143, 28, 39 });
	down.PushBack({ 193, 145, 28, 39 });
	down.speed = 0.2f;

	//char left-up
	left_up.PushBack({ 57, 93, 29, 36 });
	left_up.PushBack({ 90, 93, 30, 37 });
	left_up.PushBack({ 123, 92, 30, 37 });
	left_up.PushBack({ 156, 91, 31, 35 });
	left_up.PushBack({ 202, 190, 28, 36 });
	left_up.speed = 0.2f;

	// char left-down
	left_down.PushBack({ 193, 90, 30, 37 });
	left_down.PushBack({ 20, 372, 30, 37 });
	left_down.PushBack({ 53, 374, 31, 38 });
	left_down.PushBack({ 91, 374, 31, 39 });
	left_down.PushBack({ 128, 376, 28, 37 });
	left_down.speed = 0.2f;

	// char right-down
	right_down.PushBack({ 18, 41, 25, 38 });
	right_down.PushBack({ 51, 44, 28, 38 });
	right_down.PushBack({ 86, 45, 28, 37 });
	right_down.PushBack({ 121, 45, 27, 37 });
	right_down.PushBack({ 157, 46, 27, 37 });
	right_down.speed = 0.2f;

	// char right-up
	right_up.PushBack({ 20, 329, 24, 37 });
	right_up.PushBack({ 50, 326, 25, 38 });
	right_up.PushBack({ 82, 325, 24, 36 });
	right_up.PushBack({ 114, 323, 25, 37 });
	right_up.speed = 0.2f;

	//laser 180º
	laser_360.PushBack({ 55, 192, 29, 35 });  //-- left
	laser_360.PushBack({ 202, 190, 28, 36 }); //-- left-up
	laser_360.PushBack({ 202, 190, 28, 36 }); //-- left-up
	laser_360.PushBack({ 202, 190, 28, 36 }); //-- left-up
	laser_360.PushBack({ 17, 273, 29, 38 });  //-- up
	laser_360.PushBack({ 18, 230, 27, 36 });  //-- right-up
	laser_360.PushBack({ 18, 230, 27, 36 });  //-- right-up
	laser_360.PushBack({ 18, 230, 27, 36 });  //-- right-up
	laser_360.PushBack({ 55, 231, 29, 35 });  //-- right
	laser_360.PushBack({ 18, 139, 27, 37 });  //-- right-down
	laser_360.PushBack({ 18, 139, 27, 37 });  //-- right-down
	laser_360.PushBack({ 18, 139, 27, 37 });  //-- right-down
	laser_360.PushBack({ 54, 139, 31, 39 });  //-- down
	laser_360.PushBack({ 19, 90, 31, 39 });  //-- left-down
	laser_360.PushBack({ 19, 90, 31, 39 });  //-- left-down
	laser_360.PushBack({ 19, 90, 31, 39 });  //-- left-down
	laser_360.speed = 0.8f;
	laser_360.SetInitialFrame(UP);

	//// MULTI LASER ANIMATIONS

	//multi 360
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.PushBack({ 146, 431, 30, 36 });
	multi_360.speed = 0.8f;

	//multi up
	multi_up.PushBack({ 19, 432, 30, 37 });
	multi_up.PushBack({ 62, 432, 30, 37 });
	multi_up.PushBack({ 103, 431, 30, 37 });
	multi_up.PushBack({ 146, 431, 30, 36 });
	multi_up.PushBack({ 191, 432, 30, 37 });
	multi_up.speed = 0.2f;

	//multi down
	multi_down.PushBack({ 19, 488, 30, 37 });
	multi_down.PushBack({ 62, 489, 30, 36 });
	multi_down.PushBack({ 102, 488, 30, 37 });
	multi_down.PushBack({ 146, 488, 30, 37 });
	multi_down.PushBack({ 191, 489, 30, 37 });
	multi_down.speed = 0.2f;

	//multi left
	multi_left.PushBack({ 21, 544, 30, 36 });
	multi_left.PushBack({ 63, 543, 30, 37 });
	multi_left.PushBack({ 105, 543, 30, 37 });
	multi_left.PushBack({ 147, 543, 30, 37 });
	multi_left.PushBack({ 189, 543, 30, 37 });
	multi_left.speed = 0.2f;

	//multi right
	multi_right.PushBack({ 22, 594, 30, 37 });
	multi_right.PushBack({ 64, 594, 30, 37 });
	multi_right.PushBack({ 108, 594, 30, 37 });
	multi_right.PushBack({ 150, 594, 30, 37 });
	multi_right.PushBack({ 189, 595, 30, 36 });
	multi_right.speed = 0.2f;

	//bomb anim
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 240, 0, 240, 320 });
	bomb.PushBack({ 480, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 720, 0, 240, 320 });
	bomb.PushBack({ 960, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 1200, 0, 240, 320 });
	bomb.PushBack({ 1440, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 1680, 0, 240, 320 });
	bomb.PushBack({ 1920, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 2160, 0, 240, 320 });
	bomb.PushBack({ 2400, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 2640, 0, 240, 320 });
	bomb.PushBack({ 2880, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 3120, 0, 240, 320 });
	bomb.PushBack({ 3360, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.PushBack({ 3600, 0, 240, 320 });
	bomb.PushBack({ 3840, 0, 240, 320 });
	bomb.PushBack({ 0, 0, 240, 320 }); //-- yellow flash
	bomb.speed = 0.3f;
	bomb.loop = false;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	main_char_tex = App->textures->Load("Sprites/Main Char/Main_moves.png");
	bomb_tex = App->textures->Load("Sprites/Weapon Shots/bomb.png");
	bomb_pressed = false;
	current_animation = &up;
	bool ret = true;
	weapon_anim = &laser_360;
	multi_360.SetInitialFrame(UP);
	current_weapon = LASER;
	last_basic_weapon = LASER;
	current_power = P0;
	direction = IDLE;
	laser_p0 = &App->particles->basic_laser_p0;
	laser_p1 = &App->particles->basic_laser_p1;
	laser_p2 = &App->particles->basic_laser_p2;
	shoot_start = &App->particles->shoot_start;
	laser_end = &App->particles->laser_end;
	multi_laser_p0 = &App->particles->multi_laser_p0;
	multi_laser_p1 = &App->particles->multi_laser_p1;
	multi_laser_p2 = &App->particles->multi_laser_p2;
	multi_start = &App->particles->multi_start;
	multi_end = &App->particles->multi_end;

	ResetPosition();

	return ret;
}

bool ModulePlayer::CleanUp(){

	LOG("Player CleanUp--------");

	App->textures->Unload(main_char_tex);
	App->textures->Unload(bomb_tex);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 1.7f;

	// change weapon
	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN){ 
		current_weapon = ChangeWeapon(current_weapon);
		last_basic_weapon = current_weapon;
	} 

	//power up
	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN){
		if (current_power == P0) current_power = P1;
		else if (current_power == P1)current_power = P2;
		SDL_SetTextureColorMod(main_char_tex, 255, 120, 86);
	}

	//power down
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN){
		if (current_power == P2) current_power = P1;
		else if (current_power == P1)current_power = P0;
	}

	// Shoot key
	if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN){
		CreateShoot(current_weapon, weapon_anim);
	}

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN){
		bomb_pressed = true;
	}

	// W key
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
		direction = UP;
		current_animation = SelectAnimation(direction);
		if (position.y < 160){
			App->levels->camera_y += speed; // = to character speed
		}
		else{
			position.y -= speed; // - is + character speed
		}
	}
	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP){
		direction = IDLE;
	}
	///////////////////////////////////////////////////////////////////////////////////////

	// D key
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
		if (position.x <SCREEN_WIDTH-29){
			position.x += speed;
		}
		direction = RIGHT;
		current_animation = SelectAnimation(direction);
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
			direction = RIGHT_UP;
			current_animation = SelectAnimation(direction);
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT){
			direction = RIGHT_DOWN;
			current_animation = SelectAnimation(direction);
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
			direction = IDLE;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP){
		direction = IDLE;
	}
	///////////////////////////////////////////////////////////////////////////////////////

	// A key
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
		if (position.x > 0 ){
			position.x -= speed;
		}
		direction = LEFT;
		current_animation = SelectAnimation(direction);
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
			direction = LEFT_UP;
			current_animation = SelectAnimation(direction);
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT){
			direction = LEFT_DOWN;
			current_animation = SelectAnimation(direction);
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
				direction = IDLE;
				if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
					direction = UP;
					current_animation = SelectAnimation(direction);
				}
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP){
			direction = IDLE;
	}
	///////////////////////////////////////////////////////////////////////////////////////

	// S key
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT){
		if(position.y < SCREEN_HEIGHT-38)position.y+= speed; // + is - character speed
		direction = DOWN;
		current_animation = SelectAnimation(direction);
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE :: KEY_REPEAT){
				direction = IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
			direction = LEFT_DOWN;
			current_animation = SelectAnimation(direction);
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
			direction = RIGHT_DOWN;
			current_animation = SelectAnimation(direction);
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP){
		direction = IDLE;
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP){
			direction = LEFT_DOWN;
			current_animation = SelectAnimation(direction);
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP){
			direction = RIGHT_DOWN;
			current_animation = SelectAnimation(direction);
		}
	}

	if (direction != IDLE){
		if (CheckPJAnimPos(weapon_anim, direction))
			App->render->Blit(main_char_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
		else App->render->Blit(main_char_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));
	}
	else App->render->Blit(main_char_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));

	if (bomb_pressed){
		if (!bomb.Finished()){
			App->render->Blit(bomb_tex, 0, 0, &(bomb.GetCurrentFrame()));
		}
		else{
			bomb_pressed = false;
			//bomb.Reset();
		}
	}

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CheckPJAnimPos(Animation* anim, PlayerDirection dest_anim){

	bool ret = false;
	uint FrameIndex = (uint)anim->GetFrameIndex();
	if (FrameIndex == dest_anim) ret = true;
	else {
		switch (dest_anim){
		case LEFT: if (FrameIndex > RIGHT) 
						anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_60: if (FrameIndex > ANGLE_240 || FrameIndex < ANGLE_60)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case LEFT_UP: if (FrameIndex > RIGHT_DOWN || FrameIndex < LEFT_UP)
							anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_30: if (FrameIndex > ANGLE_210 || FrameIndex < ANGLE_30)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case UP: if (FrameIndex > DOWN || FrameIndex < UP)
					 anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_330: if (FrameIndex > ANGLE_150 || FrameIndex < ANGLE_330)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case RIGHT_UP: if (FrameIndex > LEFT_DOWN || FrameIndex < RIGHT_UP) 
							anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_300: if (FrameIndex < ANGLE_300)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case RIGHT: if (FrameIndex < RIGHT) 
						anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_240: if (FrameIndex >= ANGLE_60)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case RIGHT_DOWN: if (FrameIndex >= LEFT_UP && FrameIndex < RIGHT_DOWN) 
							anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_210: if (FrameIndex >= ANGLE_30)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case DOWN: if (FrameIndex >= UP && FrameIndex < DOWN) 
						anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_150: if (FrameIndex  >= ANGLE_330)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case LEFT_DOWN: if (FrameIndex >= RIGHT_UP && FrameIndex < LEFT_DOWN) 
							anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_120: if (FrameIndex >= ANGLE_300)
							anim->AnimForward();
					   else anim->AnimBack();
					   break;

		}
	}
	return ret;
}

void ModulePlayer::CreateShoot(Weapons equiped, Animation* anim)const{

	uint FrameIndex = (uint)anim->GetFrameIndex();
	switch (equiped)
	{
	case LASER:
		switch (current_power)
		{
		case P0:
			switch (FrameIndex)
			{
			case LEFT:
				App->particles->SetParticleSpeed(laser_p0, -5, 0);
				App->particles->AddParticle(*laser_p0, position.x - 8, position.y + 1, -90);
				App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 1, -90);
				break;
			case ANGLE_60:
				App->particles->SetParticleSpeed(laser_p0, -4.61f, -1.91f);
				App->particles->AddParticle(*laser_p0, position.x, position.y - 5, -67.5);
				App->particles->AddParticle(*shoot_start, position.x - 5, position.y - 5, -67.5);
				break;
			case LEFT_UP:
				App->particles->SetParticleSpeed(laser_p0, -3.53f, -3.53f);
				App->particles->AddParticle(*laser_p0, position.x + 3, position.y - 12, -45);
				App->particles->AddParticle(*shoot_start, position.x - 2, position.y - 12, -45);
				break;
			case ANGLE_30:
				App->particles->SetParticleSpeed(laser_p0, -1.91f, -4.61f);
				App->particles->AddParticle(*laser_p0, position.x + 8, position.y - 12, -22.5);
				App->particles->AddParticle(*shoot_start, position.x + 3, position.y - 12, -22.5);
				break;
			case UP:
				App->particles->SetParticleSpeed(laser_p0, 0, -5);
				App->particles->AddParticle(*laser_p0, position.x + 21, position.y - 15);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 15);
				break;
			case ANGLE_330:
				App->particles->SetParticleSpeed(laser_p0, 1.91f, -4.61f);
				App->particles->AddParticle(*laser_p0, position.x + 25, position.y - 12, 22.5);
				App->particles->AddParticle(*shoot_start, position.x + 20, position.y - 12, 22.5);
				break;
			case RIGHT_UP:
				App->particles->SetParticleSpeed(laser_p0, 3.53f, -3.53f);
				App->particles->AddParticle(*laser_p0, position.x + 30, position.y - 12, 45);
				App->particles->AddParticle(*shoot_start, position.x + 25, position.y - 12, 45);
				break;
			case ANGLE_300:
				App->particles->SetParticleSpeed(laser_p0, 4.61f, -1.91f);
				App->particles->AddParticle(*laser_p0, position.x + 33, position.y - 5, 67.5);
				App->particles->AddParticle(*shoot_start, position.x + 28, position.y - 5, 67.5);
				break;
			case RIGHT:
				App->particles->SetParticleSpeed(laser_p0, 5, 0);
				App->particles->AddParticle(*laser_p0, position.x + 35, position.y + 2, 90);
				App->particles->AddParticle(*shoot_start, position.x + 30, position.y + 2, 90);
				break;
			case ANGLE_240:
				App->particles->SetParticleSpeed(laser_p0, 4.61f, 1.91f);
				App->particles->AddParticle(*laser_p0, position.x + 25, position.y + 15, 102.5);
				App->particles->AddParticle(*shoot_start, position.x+20, position.y + 15, 102.5);
				break;
			case RIGHT_DOWN:
				App->particles->SetParticleSpeed(laser_p0, 3.53f, 3.53f);
				App->particles->AddParticle(*laser_p0, position.x +20, position.y + 17, 135);
				App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 19, 135);
				break;
			case ANGLE_210:
				App->particles->SetParticleSpeed(laser_p0, +1.91f, +4.61f);
				App->particles->AddParticle(*laser_p0, position.x +18, position.y + 17, 167.5);
				App->particles->AddParticle(*shoot_start, position.x +15, position.y + 21, 167.5);
				break;
			case DOWN:
				App->particles->SetParticleSpeed(laser_p0, 0, 5);
				App->particles->AddParticle(*laser_p0, position.x + 8, position.y + 20,180);
				App->particles->AddParticle(*shoot_start, position.x + 3, position.y + 27, 180);
				break;
			case ANGLE_150:
				App->particles->SetParticleSpeed(laser_p0, -1.91f, 4.61f);
				App->particles->AddParticle(*laser_p0, position.x , position.y + 20, -157.5);
				App->particles->AddParticle(*shoot_start, position.x -5, position.y + 20, -157.5);
				break;
			case LEFT_DOWN:
				App->particles->SetParticleSpeed(laser_p0, -3.53f, 3.53f);
				App->particles->AddParticle(*laser_p0, position.x - 5, position.y + 17, -125);
				App->particles->AddParticle(*shoot_start, position.x -11, position.y + 17, -135);
				break;
			case ANGLE_120:
				App->particles->SetParticleSpeed(laser_p0, -4.61f, 1.91f);
				App->particles->AddParticle(*laser_p0, position.x - 5, position.y + 13, -102.5);
				App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 13, -107.5);
				break;
			}
			break;
		case P1:
			switch (FrameIndex)
			{
			case LEFT:
				App->particles->SetParticleSpeed(laser_p1, -5, 0);
				App->particles->AddParticle(*laser_p1, position.x - 8, position.y + 1, -90);
				App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 1, -90);

				break;
			case ANGLE_60:
				App->particles->SetParticleSpeed(laser_p1, -4.61f, -1.91f);
				App->particles->AddParticle(*laser_p1, position.x, position.y - 5, -67.5);
				App->particles->AddParticle(*shoot_start, position.x - 5, position.y - 5, -67.5);
				break;
			case LEFT_UP:
				App->particles->SetParticleSpeed(laser_p1, -3.53f, -3.53f);
				App->particles->AddParticle(*laser_p1, position.x + 1, position.y - 11, -45);
				App->particles->AddParticle(*shoot_start, position.x - 2, position.y - 12, -45);
				break;
			case ANGLE_30:
				App->particles->SetParticleSpeed(laser_p1, -1.91f, -4.61f);
				App->particles->AddParticle(*laser_p1, position.x + 8, position.y - 12, -22.5);
				App->particles->AddParticle(*shoot_start, position.x + 3, position.y - 12, -22.5);
				break;
			case UP:
				App->particles->SetParticleSpeed(laser_p1, 0, -5);
				App->particles->AddParticle(*laser_p1, position.x + 17, position.y - 15);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 15);
				break;
			case ANGLE_330:
				App->particles->SetParticleSpeed(laser_p1, 1.91f, -4.61f);
				App->particles->AddParticle(*laser_p1, position.x + 25, position.y - 12, 22.5);
				App->particles->AddParticle(*shoot_start, position.x + 20, position.y - 12, 22.5);
				break;
			case RIGHT_UP:
				App->particles->SetParticleSpeed(laser_p1, 3.53f, -3.53f);
				App->particles->AddParticle(*laser_p1, position.x + 30, position.y - 12, 45);
				App->particles->AddParticle(*shoot_start, position.x + 25, position.y - 12, 45);
				break;
			case ANGLE_300:
				App->particles->SetParticleSpeed(laser_p1, 4.61f, -1.91f);
				App->particles->AddParticle(*laser_p1, position.x + 33, position.y - 5, 67.5);
				App->particles->AddParticle(*shoot_start, position.x + 28, position.y - 5, 67.5);
				break;
			case RIGHT:
				App->particles->SetParticleSpeed(laser_p1, 5, 0);
				App->particles->AddParticle(*laser_p1, position.x + 35, position.y + 2, 90);
				App->particles->AddParticle(*shoot_start, position.x + 30, position.y + 2, 90);
				break;
			case ANGLE_240:
				App->particles->SetParticleSpeed(laser_p1, 4.61f, 1.91f);
				App->particles->AddParticle(*laser_p1, position.x + 25, position.y + 15, 102.5);
				App->particles->AddParticle(*shoot_start, position.x + 20, position.y + 15, 102.5);
				break;
			case RIGHT_DOWN:
				App->particles->SetParticleSpeed(laser_p1, 3.53f, 3.53f);
				App->particles->AddParticle(*laser_p1, position.x + 20, position.y + 20, 135);
				App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 19, 135);
				break;
			case ANGLE_210:
				App->particles->SetParticleSpeed(laser_p1, +1.91f, +4.61f);
				App->particles->AddParticle(*laser_p1, position.x + 18, position.y + 17, 167.5);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y + 21, 167.5);
				break;
			case DOWN:
				App->particles->SetParticleSpeed(laser_p1, 0, 5);
				App->particles->AddParticle(*laser_p1, position.x + 4, position.y + 20, 180);
				App->particles->AddParticle(*shoot_start, position.x + 3, position.y + 27, 180);
				break;
			case ANGLE_150:
				App->particles->SetParticleSpeed(laser_p1, -1.91f, 4.61f);
				App->particles->AddParticle(*laser_p1, position.x, position.y + 20, -157.5);
				App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 20, -157.5);
				break;
			case LEFT_DOWN:
				App->particles->SetParticleSpeed(laser_p1, -3.53f, 3.53f);
				App->particles->AddParticle(*laser_p1, position.x - 5, position.y + 13, -125);
				App->particles->AddParticle(*shoot_start, position.x - 11, position.y + 17, -135);
				break;
			case ANGLE_120:
				App->particles->SetParticleSpeed(laser_p1, -4.61f, 1.91f);
				App->particles->AddParticle(*laser_p1, position.x - 5, position.y + 13, -102.5);
				App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 13, -107.5);
				break;
			}
			break;
		case P2:
			switch (FrameIndex)
			{
			case LEFT:
				App->particles->SetParticleSpeed(laser_p2, -5, 0);
				App->particles->AddParticle(*laser_p2, position.x - 8, position.y - 3, -90);
				App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 1, -90);

				break;
			case ANGLE_60:
				App->particles->SetParticleSpeed(laser_p2, -4.61f, -1.91f);
				App->particles->AddParticle(*laser_p2, position.x, position.y - 5, -67.5);
				App->particles->AddParticle(*shoot_start, position.x - 5, position.y - 5, -67.5);
				break;
			case LEFT_UP:
				App->particles->SetParticleSpeed(laser_p2, -3.53f, -3.53f);
				App->particles->AddParticle(*laser_p2, position.x - 6, position.y - 16, -45);
				App->particles->AddParticle(*shoot_start, position.x - 2, position.y - 12, -45);
				break;
			case ANGLE_30:
				App->particles->SetParticleSpeed(laser_p2, -1.91f, -4.61f);
				App->particles->AddParticle(*laser_p2, position.x + 8, position.y - 12, -22.5);
				App->particles->AddParticle(*shoot_start, position.x + 3, position.y - 12, -22.5);
				break;
			case UP:
				App->particles->SetParticleSpeed(laser_p2, 0, -5);
				App->particles->AddParticle(*laser_p2, position.x + 10, position.y - 15);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 15);
				break;
			case ANGLE_330:
				App->particles->SetParticleSpeed(laser_p2, 1.91f, -4.61f);
				App->particles->AddParticle(*laser_p2, position.x + 25, position.y - 12, 22.5);
				App->particles->AddParticle(*shoot_start, position.x + 20, position.y - 12, 22.5);
				break;
			case RIGHT_UP:
				App->particles->SetParticleSpeed(laser_p2, 3.53f, -3.53f);
				App->particles->AddParticle(*laser_p2, position.x + 21, position.y - 16, 45);
				App->particles->AddParticle(*shoot_start, position.x + 25, position.y - 12, 45);
				break;
			case ANGLE_300:
				App->particles->SetParticleSpeed(laser_p2, 4.61f, -1.91f);
				App->particles->AddParticle(*laser_p2, position.x + 33, position.y - 5, 67.5);
				App->particles->AddParticle(*shoot_start, position.x + 28, position.y - 5, 67.5);
				break;
			case RIGHT:
				App->particles->SetParticleSpeed(laser_p2, 5, 0);
				App->particles->AddParticle(*laser_p2, position.x + 35, position.y - 2, 90);
				App->particles->AddParticle(*shoot_start, position.x + 30, position.y + 2, 90);
				break;
			case ANGLE_240:
				App->particles->SetParticleSpeed(laser_p2, 4.61f, 1.91f);
				App->particles->AddParticle(*laser_p2, position.x + 25, position.y + 15, 102.5);
				App->particles->AddParticle(*shoot_start, position.x + 20, position.y + 15, 102.5);
				break;
			case RIGHT_DOWN:
				App->particles->SetParticleSpeed(laser_p2, 3.53f, 3.53f);
				App->particles->AddParticle(*laser_p2, position.x + 16, position.y + 20, 135);
				App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 19, 135);
				break;
			case ANGLE_210:
				App->particles->SetParticleSpeed(laser_p2, +1.91f, +4.61f);
				App->particles->AddParticle(*laser_p2, position.x + 18, position.y + 17, 167.5);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y + 21, 167.5);
				break;
			case DOWN:
				App->particles->SetParticleSpeed(laser_p2, 0, 5);
				App->particles->AddParticle(*laser_p2, position.x - 3, position.y + 20, 180);
				App->particles->AddParticle(*shoot_start, position.x + 3, position.y + 27, 180);
				break;
			case ANGLE_150:
				App->particles->SetParticleSpeed(laser_p2, -1.91f, 4.61f);
				App->particles->AddParticle(*laser_p2, position.x, position.y + 20, -157.5);
				App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 20, -157.5);
				break;
			case LEFT_DOWN:
				App->particles->SetParticleSpeed(laser_p2, -3.53f, 3.53f);
				App->particles->AddParticle(*laser_p2, position.x - 10, position.y + 10, -125);
				App->particles->AddParticle(*shoot_start, position.x - 11, position.y + 17, -135);
				break;
			case ANGLE_120:
				App->particles->SetParticleSpeed(laser_p2, -4.61f, 1.91f);
				App->particles->AddParticle(*laser_p2, position.x - 5, position.y + 13, -102.5);
				App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 13, -107.5);
				break;
			}
			break;
		default:
			break;
		}
		
		break;
	case MULTI:
		switch (current_power)
		{
		case P0:
			App->particles->SetParticleSpeed(multi_laser_p0, 0, -5);
			App->particles->AddParticle(*multi_laser_p0, position.x+12, position.y-10);
			App->particles->SetParticleSpeed(multi_laser_p0, -1.91f, -4.61f);
			App->particles->AddParticle(*multi_laser_p0, position.x+1, position.y-10, -22.5);
			App->particles->SetParticleSpeed(multi_laser_p0, 2.91f, -4.61f);
			App->particles->AddParticle(*multi_laser_p0, position.x+23, position.y-10, 22.5);
			App->particles->AddParticle(*multi_start, position.x - 3, position.y - 15);
			break;
		case P1:
			App->particles->SetParticleSpeed(multi_laser_p1, 0, -5);
			App->particles->AddParticle(*multi_laser_p1, position.x + 10, position.y-10);
			App->particles->SetParticleSpeed(multi_laser_p1, -1.91f, -4.61f);
			App->particles->AddParticle(*multi_laser_p1, position.x + 1, position.y-10, -22.5);
			App->particles->SetParticleSpeed(multi_laser_p1, 2.91f, -4.61f);
			App->particles->AddParticle(*multi_laser_p1, position.x + 19, position.y-10, 22.5);
			App->particles->AddParticle(*multi_start, position.x - 3, position.y - 15);
			break;
		case P2:
			App->particles->SetParticleSpeed(multi_laser_p2, 0, -5);
			App->particles->AddParticle(*multi_laser_p2, position.x + 9, position.y-10);
			App->particles->SetParticleSpeed(multi_laser_p2, -1.91f, -4.61f);
			App->particles->AddParticle(*multi_laser_p2, position.x + 1, position.y-10, -22.5);
			App->particles->SetParticleSpeed(multi_laser_p2, 2.91f, -4.61f);
			App->particles->AddParticle(*multi_laser_p2, position.x + 17, position.y-8, 22.5);
			App->particles->AddParticle(*multi_start, position.x - 3, position.y - 15);
			break;
		default:
			break;
		}
		break;
	case SUPERBALL:
		break;
	case SUPERBURNER:
		break;
	default:
		break;
	}
}

Weapons ModulePlayer::ChangeWeapon(Weapons current){
	Weapons ret;
	switch (current)
	{
	case LASER:
		ret = MULTI;
		weapon_anim = &multi_360;
		break;
	case MULTI:
		ret = LASER;
		weapon_anim = &laser_360;
		break;
	case SUPERBALL:
		ret = last_basic_weapon;
		if (last_basic_weapon == LASER)
			weapon_anim = &laser_360;
		else weapon_anim = &multi_360;
		break;
	case SUPERBURNER:
		ret = last_basic_weapon;
		if (last_basic_weapon == LASER)
			weapon_anim = &laser_360;
		else weapon_anim = &multi_360;
		break;
	}

	return ret;
}

Animation* ModulePlayer::SelectAnimation(PlayerDirection direction){

	Animation* ret = current_animation;
	switch (current_weapon)
	{
	case LASER:
		switch (direction)
		{
		case LEFT:
			ret = &left;
			break;
		case LEFT_UP:
			ret = &left_up;
			break;
		case UP:
			ret = &up;
			break;
		case RIGHT_UP:
			ret = &right_up;
			break;
		case RIGHT:
			ret = &right;
			break;
		case RIGHT_DOWN:
			ret = &right_down;
			break;
		case DOWN:
			ret = &down;
			break;
		case LEFT_DOWN:
			ret = &left_down;
			break;
		}
		break;
	case MULTI:
		switch (direction)
		{
		case LEFT:
			ret = &multi_left;
			break;
		case LEFT_UP:
			ret = &multi_up;
			break;
		case UP:
			ret = &multi_up;
			break;
		case RIGHT_UP:
			ret = &multi_up;
			break;
		case RIGHT:
			ret = &multi_right;
			break;
		case RIGHT_DOWN:
			ret = &multi_down;
			break;
		case DOWN:
			ret = &multi_down;
			break;
		case LEFT_DOWN:
			ret = &multi_down;
			break;
		}
		break;
	case SUPERBALL:
		break;
	case SUPERBURNER:
		break;
	default:
		break;
	}

	return ret;
}

void ModulePlayer::ResetPosition(){
	position.x = 120;
	position.y = 245;
}