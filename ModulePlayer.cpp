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

	//Char Up anim
	up.PushBack({ 17, 273, 29, 38 });
	up.PushBack({ 55, 274, 27, 37 });
	up.PushBack({ 90, 274, 27, 37 });
	up.PushBack({ 126, 273, 26, 37 });
	up.PushBack({ 161, 274, 28, 37 });
	up.speed = 0.1f;

	//char right
	right.PushBack({ 94, 230, 27, 35 });
	right.PushBack({ 131, 230, 25, 36 });
	right.PushBack({ 166, 231, 28, 35 });
	right.PushBack({ 204, 230, 26, 37 });
	right.PushBack({ 55, 231, 29, 35 });
	right.speed = 0.1f;

	//char left
	left.PushBack({ 166, 191, 29, 35 });
	left.PushBack({ 131, 192, 28, 33 });
	left.PushBack({ 93, 191, 28, 35 });
	left.PushBack({ 55, 192, 29, 35 });
	left.PushBack({ 18, 191, 27, 35 });
	left.speed = 0.1f;

	//char down
	down.PushBack({ 54, 139, 31, 39 });
	down.PushBack({ 92, 141, 28, 39 });
	down.PushBack({ 125, 143, 27, 37 });
	down.PushBack({ 158, 143, 28, 39 });
	down.PushBack({ 193, 145, 28, 39 });
	down.speed = 0.1f;

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

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	main_char_tex = App->textures->Load("Sprites/Main Char/Main_moves.png");
	current_animation = &up;
	bool ret = true;
	weapon_anim = &laser_360;
	current_weapon = LASER_P0;
	direction = IDLE;
	laser_p0 = &App->particles->basic_laser_p0;
	shoot_start = &App->particles->shoot_start;
	laser_end = &App->particles->laser_end;
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	// Shoot key
	if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN){
		CreateShoot(current_weapon, weapon_anim);
	}

	// W key
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
		current_animation = &up;
		direction = UP;
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
		current_animation = &right;
		if (position.x <SCREEN_WIDTH-29){
			position.x += speed;
		}
		direction = RIGHT;
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
			direction = RIGHT_UP;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP){
		direction = IDLE;
	}
	///////////////////////////////////////////////////////////////////////////////////////

	// A key
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
		current_animation = &left;
		if (position.x > 0 ){
			position.x -= speed;
		}
		direction = LEFT;
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
			direction = LEFT_UP;
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
				direction = UP;
				current_animation = &up;
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
	}
	if (direction != IDLE){
		if (CheckPJAnimPos(weapon_anim, direction))
			App->render->Blit(main_char_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
		else App->render->Blit(main_char_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));
	}
	else App->render->Blit(main_char_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CheckPJAnimPos(Animation* anim, PlayerDirection dest_anim){

	bool ret = false;
	uint FrameIndex = (uint)anim->GetFrameIndex();
	if (FrameIndex == dest_anim) ret = true;
	else {
		switch (dest_anim){
		case LEFT: if (FrameIndex > RIGHT) anim->AnimForward();
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
		case ANGLE_240: if (FrameIndex > 9 || FrameIndex < ANGLE_60)
			anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case RIGHT_DOWN: if (FrameIndex > 8) anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_210: if (FrameIndex > 9 || FrameIndex < ANGLE_60)
			anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case DOWN: if (FrameIndex > 8) anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_150: if (FrameIndex > 9 || FrameIndex < ANGLE_60)
			anim->AnimForward();
					   else anim->AnimBack();
					   break;
		case LEFT_DOWN: if (FrameIndex > 8) anim->AnimForward();
				   else anim->AnimBack();
				   break;
		case ANGLE_120: if (FrameIndex > 9 || FrameIndex < ANGLE_60)
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
	case LASER_P0:
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
			App->particles->AddParticle(*shoot_start, position.x-5, position.y - 5, -67.5);
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
			App->particles->AddParticle(*laser_p0, position.x + 19, position.y - 15);
			App->particles->AddParticle(*shoot_start, position.x + 14, position.y - 15);
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
			break;
		case RIGHT_DOWN:
			break;
		case ANGLE_210:
			break;
		case DOWN:
			break;
		case ANGLE_150:
			break;
		case LEFT_DOWN:
			break;
		case ANGLE_120:
			break;
		default:
			break;
		}
		break;
	case LASER_P1:
		break;
	case LASER_P2:
		break;
	case MULTI_P0:
		break;
	case MULTI_P1:
		break;
	case MULTI_P2:
		break;
	case SUPERBALL:
		break;
	case SUPERBURNER:
		break;
	default:
		break;
	}
}