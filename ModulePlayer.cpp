#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneLevels.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleBomb.h"
#include "ModuleUI.h"

#define nullrect {0,0,0,0} 
#define laserbox_p0 {0,0,4,4}
#define laserbox_p1 {0,0,8,8}
#define laserbox_p2 {0,0,22,22}

ModulePlayer::ModulePlayer()
{
	position.x = 120;
	position.y = 15308;

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

	// char fall in a hole
	fall_hole.PushBack({ 6, 645, 32, 37 });
	fall_hole.PushBack({ 45, 649, 31, 30 });
	fall_hole.PushBack({ 83, 650, 30, 32 });
	fall_hole.PushBack({ 123, 653, 27, 22 });
	fall_hole.PushBack({ 156, 653, 21, 26 });
	fall_hole.PushBack({ 187, 655, 26, 22 });
	fall_hole.PushBack({ 223, 653, 11, 21 });
	fall_hole.speed = 0.1f;
	fall_hole.loop = false;

	//laser 360
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
	laser_360.speed = 1.0f;
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
	bomb.speed = 0.8f;
	bomb.loop = false;

	dead_explo.PushBack({ 0, 0, 117, 115 });
	dead_explo.PushBack({ 117, 0, 117, 115 });
	dead_explo.PushBack({ 234, 0, 117, 115 });
	dead_explo.PushBack({ 351, 0, 117, 115 });
	dead_explo.PushBack({ 468, 0, 117, 115 });
	dead_explo.PushBack({ 585, 0, 117, 115 });
	dead_explo.PushBack({ 702, 0, 117, 115 });
	dead_explo.PushBack({ 819, 0, 117, 115 });
	dead_explo.PushBack({ 936, 0, 117, 115 });
	dead_explo.speed = 0.2f;
	dead_explo.loop = false;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	main_char_tex = App->textures->Load("OutZone/Sprites/Main Char/Main_moves.png");
	bomb_tex = App->textures->Load("OutZone/Sprites/Weapon Shots/bomb.png");
	dead_explo_text = App->textures->Load("OutZone/Sprites/Main Char/Dead_char_explosion.png"); 
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
	last_laser = SDL_GetTicks();
	last_multi = SDL_GetTicks();
	ResetPosition();
	move_up = move_down = move_left = move_right = true;

	PlayerCollider = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_PLAYER, this);
	PlayerEBulletsCollider = App->collisions->AddCollider({ 0, 0, 22, 25 }, COLLIDER_PLAYER_EBULLETS, this);

	return ret;
}

bool ModulePlayer::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;
	dead_fall = false;
	fall_hole.Reset();
	dead_explo.Reset();

	App->textures->Unload(main_char_tex);
	App->textures->Unload(bomb_tex);
	App->textures->Unload(dead_explo_text);

	return true;
}

update_status ModulePlayer::PostUpdate(){

	if (!dead){
		int speed = 2;
		// W key
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
			direction = UP;
			current_animation = SelectAnimation(direction);
			if ((App->render->camera.y / 3 - 200) + (position.y) < 0 && App->render->camera.y < 0){
				App->render->camera.y += 6;
				position.y -= speed;
			}
			else if (move_up) 
				position.y -= speed; // - is + character speed
		}
		else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP){
			direction = IDLE;
		}

		// D key
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
			if (position.x < SCREEN_WIDTH - 29 && move_right) 
				position.x += speed;
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
		
		//A key
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
			if (position.x > 0 && move_left) 
				position.x -= speed;
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
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP){
				direction = LEFT_DOWN;
				current_animation = SelectAnimation(direction);
			}
		}

		//S key
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT){
			if ((App->render->camera.y / 3 - 200) + (position.y) < 88 && move_down) 
				position.y += speed; // + is - character speed
			direction = DOWN;
			current_animation = SelectAnimation(direction);
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
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
		}

		
	}
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	PreviousPos = position;
	int speed = 2;
	now = SDL_GetTicks();


	if (!dead){
		//TP last checkpoint
		if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN){
			App->ui->curr_check = 13;
		}
		// change weapon
		if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN){
			current_weapon = ChangeWeapon(current_weapon);
			last_basic_weapon = current_weapon;
		}

		//power up
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN){
			if (current_power == P0) current_power = P1;
			else if (current_power == P1)current_power = P2;
			//SDL_SetTextureColorMod(main_char_tex, 255, 120, 86);
		}

		//power down
		if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN){
			if (current_power == P2) current_power = P1;
			else if (current_power == P1)current_power = P0;
		}

		// Shoot key
		if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN){
			if (current_weapon == MULTI){
				CreateShoot(current_weapon, weapon_anim);
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_REPEAT){
			if (current_weapon == LASER){
				if (pos_changed&&now - last_laser > 30){
					CreateShoot(current_weapon, weapon_anim);
					pos_changed = false;
					last_laser = SDL_GetTicks();
				}
				else if (now - last_laser > 140){
					CreateShoot(current_weapon, weapon_anim);
					last_laser = SDL_GetTicks();
				}
			}
			else if (current_weapon == MULTI){
				if (now - last_multi > 1000){
					CreateShoot(current_weapon, weapon_anim);
					last_multi = SDL_GetTicks();
				}
			}
		}

		//Special attack key
		if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN && App->ui->bombs>0){
			App->bomb->pressed = true;
			App->ui->SubBomb();
		}	

		if (direction != IDLE){
			if (CheckPJAnimPos(weapon_anim, direction))
				App->render->Blit(main_char_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
			else App->render->Blit(main_char_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));
		}
		else App->render->Blit(main_char_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));
	}
	else{
		if (dead_fall){
			if (fall_hole.Finished()){
				App->ui->dead = true;
				fall_hole.Finished();
			}
			else
				App->render->Blit(main_char_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
		}
		else{
			if (dead_explo.Finished()){
				Player_explosion->to_delete = true;
				collider_create = false;
				App->ui->dead = true;
			}
			else{
				App->render->Blit(dead_explo_text, position.x - 40, position.y - 39, &(current_animation->GetCurrentFrame()));
				if (!collider_create){
					Player_explosion = App->collisions->AddCollider({ position.x - 60, position.y - 60, 117, 115 }, COLLIDER_DEAD_EXPLO, this);
					collider_create = true;
				}
			}
				
		}
	}

	PlayerCollider->SetPos(position.x+10, position.y+20);
	PlayerEBulletsCollider->SetPos(position.x+4 , position.y+3);
	
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CheckPJAnimPos(Animation* anim, Direction dest_anim){

	bool ret = false;
	uint FrameIndex = (uint)anim->GetFrameIndex();
	if (FrameIndex == dest_anim) ret = true;
	else {
		pos_changed = true;
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
				App->particles->SetColliderCorrection(laser_p0, -6, 6);
				App->particles->AddParticle(*laser_p0, position.x - 8, position.y + 1, laser_p0->collider, laserbox_p0, -90);
				App->particles->AddParticle(*shoot_start, position.x - 10, position.y + 1, shoot_start->collider, nullrect, -90);
				break;
			case ANGLE_60:
				App->particles->SetParticleSpeed(laser_p0, -4.61f, -1.91f);
				App->particles->SetColliderCorrection(laser_p0, -5, 4);
				App->particles->AddParticle(*laser_p0, position.x, position.y - 5, laser_p0->collider, laserbox_p0, -67.5);
				App->particles->AddParticle(*shoot_start, position.x - 3, position.y - 3, shoot_start->collider, nullrect, -67.5);
				break;
			case LEFT_UP:
				App->particles->SetParticleSpeed(laser_p0, -3.53f, -3.53f);
				App->particles->SetColliderCorrection(laser_p0, -4, 2);
				App->particles->AddParticle(*laser_p0, position.x + 3, position.y - 12, laser_p0->collider, laserbox_p0, -45);
				App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 9, shoot_start->collider, nullrect, -45);
				break;
			case ANGLE_30:
				App->particles->SetParticleSpeed(laser_p0, -1.91f, -4.61f);
				App->particles->SetColliderCorrection(laser_p0, -2, 1);
				App->particles->AddParticle(*laser_p0, position.x + 8, position.y - 12, laser_p0->collider, laserbox_p0, -22.5);
				App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 10, shoot_start->collider, nullrect, -22.5);
				break;
			case UP:
				App->particles->SetParticleSpeed(laser_p0, 0, -5);
				App->particles->SetColliderCorrection(laser_p0, 0, 0);
				App->particles->AddParticle(*laser_p0, position.x + 21, position.y - 15, laser_p0->collider, laserbox_p0);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 12, shoot_start->collider, nullrect);
				break;
			case ANGLE_330:
				App->particles->SetParticleSpeed(laser_p0, 1.91f, -4.61f);
				App->particles->SetColliderCorrection(laser_p0, 1, 0);
				App->particles->AddParticle(*laser_p0, position.x + 25, position.y - 12, laser_p0->collider, laserbox_p0, 12.5);
				App->particles->AddParticle(*shoot_start, position.x + 22, position.y - 10, shoot_start->collider, nullrect, 12.5);
				break;
			case RIGHT_UP:
				App->particles->SetParticleSpeed(laser_p0, 3.53f, -3.53f);
				App->particles->SetColliderCorrection(laser_p0, 4, 2);
				App->particles->AddParticle(*laser_p0, position.x + 30, position.y - 12, laser_p0->collider, laserbox_p0, 45);
				App->particles->AddParticle(*shoot_start, position.x + 23, position.y - 10, shoot_start->collider, nullrect, 45);
				break;
			case ANGLE_300:
				App->particles->SetParticleSpeed(laser_p0, 4.61f, -1.91f);
				App->particles->SetColliderCorrection(laser_p0, 5, 4);
				App->particles->AddParticle(*laser_p0, position.x + 33, position.y - 5, laser_p0->collider, laserbox_p0, 67.5);
				App->particles->AddParticle(*shoot_start, position.x + 26, position.y - 3, shoot_start->collider, nullrect, 67.5);
				break;
			case RIGHT:
				App->particles->SetParticleSpeed(laser_p0, 5, 0);
				App->particles->SetColliderCorrection(laser_p0, 6, 6);
				App->particles->AddParticle(*laser_p0, position.x + 35, position.y + 2, laser_p0->collider, laserbox_p0, 90);
				App->particles->AddParticle(*shoot_start, position.x + 26, position.y + 2, shoot_start->collider, nullrect, 90);
				break;
			case ANGLE_240:
				App->particles->SetParticleSpeed(laser_p0, 4.61f, 1.91f);
				App->particles->SetColliderCorrection(laser_p0, 6, 7);
				App->particles->AddParticle(*laser_p0, position.x + 25, position.y + 15, laser_p0->collider, laserbox_p0, 102.5);
				App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 13, shoot_start->collider, nullrect, 102.5);
				break;
			case RIGHT_DOWN:
				App->particles->SetParticleSpeed(laser_p0, 3.53f, 3.53f);
				App->particles->SetColliderCorrection(laser_p0, 4, 10);
				App->particles->AddParticle(*laser_p0, position.x + 20, position.y + 17, laser_p0->collider, laserbox_p0, 135);
				App->particles->AddParticle(*shoot_start, position.x + 16, position.y + 17, shoot_start->collider, nullrect, 135);
				break;
			case ANGLE_210:
				App->particles->SetParticleSpeed(laser_p0, +1.91f, +4.61f);
				App->particles->SetColliderCorrection(laser_p0, 1, 12);
				App->particles->AddParticle(*laser_p0, position.x + 18, position.y + 17, laser_p0->collider, laserbox_p0, 167.5);
				App->particles->AddParticle(*shoot_start, position.x + 13, position.y + 19, shoot_start->collider, nullrect, 167.5);
				break;
			case DOWN:
				App->particles->SetParticleSpeed(laser_p0, 0, 5);
				App->particles->SetColliderCorrection(laser_p0, 0, 12);
				App->particles->AddParticle(*laser_p0, position.x + 8, position.y + 20, laser_p0->collider, laserbox_p0, 180);
				App->particles->AddParticle(*shoot_start, position.x + 2, position.y + 24, shoot_start->collider, nullrect, 180);
				break;
			case ANGLE_150:
				App->particles->SetParticleSpeed(laser_p0, -1.91f, 4.61f);
				App->particles->SetColliderCorrection(laser_p0, -2, 12);
				App->particles->AddParticle(*laser_p0, position.x, position.y + 20, laser_p0->collider, laserbox_p0, -157.5);
				App->particles->AddParticle(*shoot_start, position.x - 3, position.y + 18, shoot_start->collider, nullrect, -157.5);
				break;
			case LEFT_DOWN:
				App->particles->SetParticleSpeed(laser_p0, -3.53f, 3.53f);
				App->particles->SetColliderCorrection(laser_p0, -5, 10);
				App->particles->AddParticle(*laser_p0, position.x - 5, position.y + 17, laser_p0->collider, laserbox_p0, -125);
				App->particles->AddParticle(*shoot_start, position.x - 9, position.y + 15, shoot_start->collider, nullrect, -135);
				break;
			case ANGLE_120:
				App->particles->SetParticleSpeed(laser_p0, -4.61f, 1.91f);
				App->particles->SetColliderCorrection(laser_p0, -6, 8);
				App->particles->AddParticle(*laser_p0, position.x - 5, position.y + 13, laser_p0->collider, laserbox_p0, -102.5);
				App->particles->AddParticle(*shoot_start, position.x - 11, position.y + 11, shoot_start->collider, nullrect, -107.5);
				break;
			}
			break;
		case P1:
			switch (FrameIndex)
			{
			case LEFT:
				App->particles->SetParticleSpeed(laser_p1, -5, 0);
				App->particles->SetColliderCorrection(laser_p1, -3, 4);
				App->particles->AddParticle(*laser_p1, position.x - 8, position.y + 1, laser_p1->collider, laserbox_p1, -90);
				App->particles->AddParticle(*shoot_start, position.x - 10, position.y + 1, shoot_start->collider, nullrect, -90);
				break;
			case ANGLE_60:
				App->particles->SetParticleSpeed(laser_p1, -4.61f, -1.91f);
				App->particles->SetColliderCorrection(laser_p1, -3, 2);
				App->particles->AddParticle(*laser_p1, position.x, position.y - 5, laser_p1->collider, laserbox_p1, -67.5);
				App->particles->AddParticle(*shoot_start, position.x - 3, position.y - 3, shoot_start->collider, nullrect, -67.5);
				break;
			case LEFT_UP:
				App->particles->SetParticleSpeed(laser_p1, -3.53f, -3.53f);
				App->particles->SetColliderCorrection(laser_p1, -1, 2);
				App->particles->AddParticle(*laser_p1, position.x + 1, position.y - 11, laser_p1->collider, laserbox_p1, -45);
				App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 9, shoot_start->collider, nullrect, -45);
				break;
			case ANGLE_30:
				App->particles->SetParticleSpeed(laser_p1, -1.91f, -4.61f);
				App->particles->SetColliderCorrection(laser_p1, -1, 0);
				App->particles->AddParticle(*laser_p1, position.x + 8, position.y - 12, laser_p1->collider, laserbox_p1, -22.5);
				App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 10, shoot_start->collider, nullrect, -22.5);
				break;
			case UP:
				App->particles->SetParticleSpeed(laser_p1, 0, -5);
				App->particles->SetColliderCorrection(laser_p1, 1, 0);
				App->particles->AddParticle(*laser_p1, position.x + 17, position.y - 15, laser_p1->collider, laserbox_p1);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 12, shoot_start->collider, nullrect);
				break;
			case ANGLE_330:
				App->particles->SetParticleSpeed(laser_p1, 1.91f, -4.61f);
				App->particles->SetColliderCorrection(laser_p1, 3, 0);
				App->particles->AddParticle(*laser_p1, position.x + 25, position.y - 12, laser_p1->collider, laserbox_p1, 22.5);
				App->particles->AddParticle(*shoot_start, position.x + 22, position.y - 10, shoot_start->collider, nullrect, 12.5);
				break;
			case RIGHT_UP:
				App->particles->SetParticleSpeed(laser_p1, 3.53f, -3.53f);
				App->particles->SetColliderCorrection(laser_p1, 4, 1);
				App->particles->AddParticle(*laser_p1, position.x + 30, position.y - 12, laser_p1->collider, laserbox_p1, 45);
				App->particles->AddParticle(*shoot_start, position.x + 23, position.y - 10, shoot_start->collider, nullrect, 45);
				break;
			case ANGLE_300:
				App->particles->SetParticleSpeed(laser_p1, 4.61f, -1.91f);
				App->particles->SetColliderCorrection(laser_p1, 5, 2);
				App->particles->AddParticle(*laser_p1, position.x + 33, position.y - 5, laser_p1->collider, laserbox_p1, 67.5);
				App->particles->AddParticle(*shoot_start, position.x + 26, position.y - 3, shoot_start->collider, nullrect, 67.5);
				break;
			case RIGHT:
				App->particles->SetParticleSpeed(laser_p1, 5, 0);
				App->particles->SetColliderCorrection(laser_p1, 5, 4);
				App->particles->AddParticle(*laser_p1, position.x + 35, position.y + 2, laser_p1->collider, laserbox_p1, 90);
				App->particles->AddParticle(*shoot_start, position.x + 26, position.y + 2, shoot_start->collider, nullrect, 90);
				break;
			case ANGLE_240:
				App->particles->SetParticleSpeed(laser_p1, 4.61f, 1.91f);
				App->particles->SetColliderCorrection(laser_p1, 5, 5);
				App->particles->AddParticle(*laser_p1, position.x + 25, position.y + 15, laser_p1->collider, laserbox_p1, 102.5);
				App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 13, shoot_start->collider, nullrect, 102.5);
				break;
			case RIGHT_DOWN:
				App->particles->SetParticleSpeed(laser_p1, 3.53f, 3.53f);
				App->particles->SetColliderCorrection(laser_p1, 4, 7);
				App->particles->AddParticle(*laser_p1, position.x + 20, position.y + 20, laser_p1->collider, laserbox_p1, 135);
				App->particles->AddParticle(*shoot_start, position.x + 16, position.y + 17, shoot_start->collider, nullrect, 135);
				break;
			case ANGLE_210:
				App->particles->SetParticleSpeed(laser_p1, +1.91f, +4.61f);
				App->particles->SetColliderCorrection(laser_p1, 2, 8);
				App->particles->AddParticle(*laser_p1, position.x + 18, position.y + 17, laser_p1->collider, laserbox_p1, 167.5);
				App->particles->AddParticle(*shoot_start, position.x + 13, position.y + 19, shoot_start->collider, nullrect, 167.5);
				break;
			case DOWN:
				App->particles->SetParticleSpeed(laser_p1, 0, 5);
				App->particles->SetColliderCorrection(laser_p1, 1, 8);
				App->particles->AddParticle(*laser_p1, position.x + 4, position.y + 20, laser_p1->collider, laserbox_p1, 180);
				App->particles->AddParticle(*shoot_start, position.x + 2, position.y + 24, shoot_start->collider, nullrect, 180);
				break;
			case ANGLE_150:
				App->particles->SetParticleSpeed(laser_p1, -1.91f, 4.61f);
				App->particles->SetColliderCorrection(laser_p1, 0, 8);
				App->particles->AddParticle(*laser_p1, position.x, position.y + 20, laser_p1->collider, laserbox_p1, -157.5);
				App->particles->AddParticle(*shoot_start, position.x - 3, position.y + 18, shoot_start->collider, nullrect, -157.5);
				break;
			case LEFT_DOWN:
				App->particles->SetParticleSpeed(laser_p1, -3.53f, 3.53f);
				App->particles->SetColliderCorrection(laser_p1, -2, 6);
				App->particles->AddParticle(*laser_p1, position.x - 5, position.y + 13, laser_p1->collider, laserbox_p1, -125);
				App->particles->AddParticle(*shoot_start, position.x - 9, position.y + 15, shoot_start->collider, nullrect, -135);
				break;
			case ANGLE_120:
				App->particles->SetParticleSpeed(laser_p1, -4.61f, 1.91f);
				App->particles->SetColliderCorrection(laser_p1, -3, 6);
				App->particles->AddParticle(*laser_p1, position.x - 5, position.y + 13, laser_p1->collider, laserbox_p1, -102.5);
				App->particles->AddParticle(*shoot_start, position.x - 11, position.y + 11, shoot_start->collider, nullrect, -107.5);
				break;
			}
			break;
		case P2:
			switch (FrameIndex)
			{
			case LEFT:
				App->particles->SetParticleSpeed(laser_p2, -5, 0);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x - 30, position.y - 3, laser_p2->collider, laserbox_p2, -90);
				App->particles->AddParticle(*shoot_start, position.x - 10, position.y + 1, shoot_start->collider, nullrect, -90);
				break;
			case ANGLE_60:
				App->particles->SetParticleSpeed(laser_p2, -4.61f, -1.91f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x-10, position.y - 16, laser_p2->collider, laserbox_p2, -67.5);
				App->particles->AddParticle(*shoot_start, position.x - 3, position.y - 3, shoot_start->collider, nullrect, -67.5);
				break;
			case LEFT_UP:
				App->particles->SetParticleSpeed(laser_p2, -3.53f, -3.53f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x - 12, position.y - 22, laser_p2->collider, laserbox_p2, -45);
				App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 9, shoot_start->collider, nullrect, -45);
				break;
			case ANGLE_30:
				App->particles->SetParticleSpeed(laser_p2, -1.91f, -4.61f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x, position.y - 20, laser_p2->collider, laserbox_p2, -22.5);
				App->particles->AddParticle(*shoot_start, position.x + 1, position.y - 10, shoot_start->collider, nullrect, -22.5);
				break;
			case UP:
				App->particles->SetParticleSpeed(laser_p2, 0, -5);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 10, position.y - 25, laser_p2->collider, laserbox_p2);
				App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 12, shoot_start->collider, nullrect);
				break;
			case ANGLE_330:
				App->particles->SetParticleSpeed(laser_p2, 1.91f, -4.61f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 25, position.y - 12, laser_p2->collider, laserbox_p2, 22.5);
				App->particles->AddParticle(*shoot_start, position.x + 22, position.y - 10, shoot_start->collider, nullrect, 12.5);
				break;
			case RIGHT_UP:
				App->particles->SetParticleSpeed(laser_p2, 3.53f, -3.53f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 21, position.y - 16, laser_p2->collider, laserbox_p2, 45);
				App->particles->AddParticle(*shoot_start, position.x + 23, position.y - 10, shoot_start->collider, nullrect, 45);
				break;
			case ANGLE_300:
				App->particles->SetParticleSpeed(laser_p2, 4.61f, -1.91f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 33, position.y - 5, laser_p2->collider, laserbox_p2, 67.5);
				App->particles->AddParticle(*shoot_start, position.x + 26, position.y - 3, shoot_start->collider, nullrect, 67.5);
				break;
			case RIGHT:
				App->particles->SetParticleSpeed(laser_p2, 5, 0);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 30, position.y - 2, laser_p2->collider, laserbox_p2, 90);
				App->particles->AddParticle(*shoot_start, position.x + 26, position.y + 2, shoot_start->collider, nullrect, 90);
				break;
			case ANGLE_240:
				App->particles->SetParticleSpeed(laser_p2, 4.61f, 1.91f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 25, position.y + 15, laser_p2->collider, laserbox_p2, 102.5);
				App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 13, shoot_start->collider, nullrect, 102.5);
				break;
			case RIGHT_DOWN:
				App->particles->SetParticleSpeed(laser_p2, 3.53f, 3.53f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 16, position.y + 20, laser_p2->collider, laserbox_p2, 135);
				App->particles->AddParticle(*shoot_start, position.x + 16, position.y + 17, shoot_start->collider, nullrect, 135);
				break;
			case ANGLE_210:
				App->particles->SetParticleSpeed(laser_p2, +1.91f, +4.61f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x + 18, position.y + 17, laser_p2->collider, laserbox_p2, 167.5);
				App->particles->AddParticle(*shoot_start, position.x + 13, position.y + 19, shoot_start->collider, nullrect, 167.5);
				break;
			case DOWN:
				App->particles->SetParticleSpeed(laser_p2, 0, 5);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x - 3, position.y + 30, laser_p2->collider, laserbox_p2, 180);
				App->particles->AddParticle(*shoot_start, position.x + 2, position.y + 24, shoot_start->collider, nullrect, 180);
				break;
			case ANGLE_150:
				App->particles->SetParticleSpeed(laser_p2, -1.91f, 4.61f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x-5, position.y + 25, laser_p2->collider, laserbox_p2, -157.5);
				App->particles->AddParticle(*shoot_start, position.x - 3, position.y + 18, shoot_start->collider, nullrect, -157.5);
				break;
			case LEFT_DOWN:
				App->particles->SetParticleSpeed(laser_p2, -3.53f, 3.53f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x - 15, position.y + 15, laser_p2->collider, laserbox_p2, -125);
				App->particles->AddParticle(*shoot_start, position.x - 9, position.y + 15, shoot_start->collider, nullrect, -135);
				break;
			case ANGLE_120:
				App->particles->SetParticleSpeed(laser_p2, -4.61f, 1.91f);
				App->particles->SetColliderCorrection(laser_p2, 1, 1);
				App->particles->AddParticle(*laser_p2, position.x - 10, position.y + 18, laser_p2->collider, laserbox_p2, -102.5);
				App->particles->AddParticle(*shoot_start, position.x - 11, position.y + 11, shoot_start->collider, nullrect, -107.5);
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
			App->particles->SetColliderCorrection(multi_laser_p0, 0, 1);
			App->particles->AddParticle(*multi_laser_p0, position.x + 12, position.y - 5, multi_laser_p0->collider, { 0, 0, 6, 6});
			App->particles->SetParticleSpeed(multi_laser_p0, -1.91f, -4.61f);
			App->particles->SetColliderCorrection(multi_laser_p0, -1, 1);
			App->particles->AddParticle(*multi_laser_p0, position.x + 2, position.y - 5, multi_laser_p0->collider, { 0, 0, 6, 6 }, -22.5);
			App->particles->SetParticleSpeed(multi_laser_p0, 2.91f, -4.61f);
			App->particles->SetColliderCorrection(multi_laser_p0, 1, 1);
			App->particles->AddParticle(*multi_laser_p0, position.x + 22, position.y - 5, multi_laser_p0->collider, { 0, 0, 6, 6 }, 22.5);
			App->particles->AddParticle(*multi_start, position.x - 3, position.y - 15, multi_start->collider, { 0, 0, 0, 0 });
			break;
		case P1:
			App->particles->SetParticleSpeed(multi_laser_p1, 0, -5);
			App->particles->SetColliderCorrection(multi_laser_p1, 0, 1);
			App->particles->AddParticle(*multi_laser_p1, position.x + 10, position.y - 8, multi_laser_p1->collider, { 0, 0, 10, 10 });
			App->particles->SetParticleSpeed(multi_laser_p1, -1.91f, -4.61f);
			App->particles->SetColliderCorrection(multi_laser_p1, -1, 1);
			App->particles->AddParticle(*multi_laser_p1, position.x + 1, position.y - 8, multi_laser_p1->collider, { 0, 0, 10, 10 }, -22.5);
			App->particles->SetParticleSpeed(multi_laser_p1, 2.91f, -4.61f);
			App->particles->SetColliderCorrection(multi_laser_p1, 1, 1);
			App->particles->AddParticle(*multi_laser_p1, position.x + 20, position.y - 8, multi_laser_p1->collider, { 0, 0, 10, 10 }, 22.5);
			App->particles->AddParticle(*multi_start, position.x - 3, position.y - 15, multi_start->collider, nullrect);
			break;
		case P2:
			App->particles->SetParticleSpeed(multi_laser_p2, 0, -5);
			App->particles->SetColliderCorrection(multi_laser_p2, 0, 1);
			App->particles->AddParticle(*multi_laser_p2, position.x + 9, position.y - 10, multi_laser_p2->collider, { 0, 0, 14, 14 });
			App->particles->SetParticleSpeed(multi_laser_p2, -1.91f, -4.61f);	
			App->particles->SetColliderCorrection(multi_laser_p2, -1, 1);
			App->particles->AddParticle(*multi_laser_p2, position.x + 1, position.y - 10, multi_laser_p2->collider, { 0, 0, 14, 14 }, -22.5);
			App->particles->SetParticleSpeed(multi_laser_p2, 2.91f, -4.61f);	
			App->particles->SetColliderCorrection(multi_laser_p2, 1, 1);
			App->particles->AddParticle(*multi_laser_p2, position.x + 17, position.y - 8, multi_laser_p2->collider, { 0, 0, 14, 14 }, 22.5);
			App->particles->AddParticle(*multi_start, position.x - 3, position.y - 15, multi_start->collider, nullrect);
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

Animation* ModulePlayer::SelectAnimation(Direction direction){

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
	position.x = 105;
	position.y = 15308;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2, Direction dir) {
	if (PlayerCollider == c1 && PlayerCollider != nullptr){
		if (c2->type == COLLIDER_WALL || c2->type == COLLIDER_PASS_BULLET){
			switch (dir) {
			case UP: 
				if (move_up) {
					position.y = PreviousPos.y;
					move_up = false;
				}
				break;
			case DOWN: 
				if (move_down) {
					position.y = PreviousPos.y;
					move_down = false;
				}
				break;
			case LEFT:
				if (move_left) {
					position.x = PreviousPos.x;
					move_left = false;
				}
				break;
			case RIGHT:
				if (move_right) {
					position.x = PreviousPos.x;
					move_right = false;
				}
				break;
			}
		}
		if (c2->type == COLLIDER_HOLE){
			dead = true;
			dead_fall = true;
			current_animation = &fall_hole;
		}
	}
	if (PlayerEBulletsCollider == c1 && PlayerEBulletsCollider != nullptr){
		if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY_SHOT){
			if (!dead){
				dead = true;
				current_animation = &dead_explo;
			}
		}
	}
}

int ModulePlayer::GetDmg(){
	switch (current_weapon)
	{
	case LASER:
		switch (current_power)
		{
		case P0:
			return 6;
			break;
		case P1:
			return 10;
			break;
		case P2:
			return 30;
			break;
		}
		break;
	case MULTI:
		switch (current_power)
		{
		case P0:
			return 4;
			break;
		case P1:
			return 6;
			break;
		case P2:
			return 12;
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
/*
bool ModulePlayer::CheckColliders() {
	Playeraux = current_animation->GetActualFrame();
	for (int i = 0; i < MAX_COLLIDERS && App->collisions->colliders[i] != nullptr; i++) {
		LOG("%d", i);
		if (App->collisions->colliders[i]->CheckCollision(Playeraux))
			return true;
	}
	LOG("RETURNED");
	return false;
}*/