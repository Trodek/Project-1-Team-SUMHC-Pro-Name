#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleGreenBasic.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneLevels.h"
#include "SDL/include/SDL_timer.h"

#define nullrect {0,0,0,0} 
#define laserbox_p0 {0,0,4,4}

ModuleGreenBasic::ModuleGreenBasic()
{
	position.x = 120;
	position.y = 14000;

	//Char Up anim
	up.PushBack({ 186, 311, 26, 36 });
	up.PushBack({ 220, 310, 27, 37 });
	up.PushBack({ 255, 312, 26, 35 });
	up.PushBack({ 289, 312, 26, 35 });
	up.speed = 0.2f;

	//char right
	right.PushBack({ 19, 221, 28, 32 });
	right.PushBack({ 58, 219, 25, 32 });
	right.PushBack({ 95, 220, 27, 32 });
	right.PushBack({ 135, 219, 25, 33 });
	right.speed = 0.25f;

	//char left
	left.PushBack({ 186, 221, 25, 32 });
	left.PushBack({ 223, 221, 28, 32 });
	left.PushBack({ 260, 220, 25, 33 });
	left.PushBack({ 297, 221, 25, 33 });
	left.speed = 0.25f;

	//char down
	down.PushBack({ 19, 311, 27, 35 });
	down.PushBack({ 57, 314, 27, 32 });
	down.PushBack({ 95, 313, 32, 33 });
	down.PushBack({ 134, 315, 27, 31 });
	down.speed = 0.2f;

	//char left-up
	left_up.PushBack({ 188, 172, 26, 35 });
	left_up.PushBack({ 222, 172, 28, 35 });
	left_up.PushBack({ 258, 170, 28, 34 });
	left_up.PushBack({ 297, 170, 27, 33 });
	left_up.speed = 0.2f;

	// char left-down
	left_down.PushBack({ 186, 265, 27, 33 });
	left_down.PushBack({ 224, 265, 27, 34 });
	left_down.PushBack({ 260, 264, 25, 34 });
	left_down.PushBack({ 291, 265, 28, 34 });
	left_down.speed = 0.2f;

	// char right-down
	right_down.PushBack({ 19, 265, 27, 34 });
	right_down.PushBack({ 54, 266, 26, 33 });
	right_down.PushBack({ 91, 266, 27, 33 });
	right_down.PushBack({ 129, 266, 26, 35 });
	right_down.speed = 0.2f;

	// char right-up
	right_up.PushBack({ 16, 173, 29, 34 });
	right_up.PushBack({ 57, 173, 26, 34 });
	right_up.PushBack({ 96, 173, 24, 33 });
	right_up.PushBack({ 131, 171, 25, 36 });
	right_up.speed = 0.2f;

	// char die
	die.PushBack({ 0, 0, 44, 46 });
	die.PushBack({ 44, 0, 44, 46 });
	die.PushBack({ 88, 0, 44, 46 });
	die.PushBack({ 132, 0, 44, 46 });
	die.PushBack({ 176, 0, 44, 46 });
	die.PushBack({ 220, 0, 44, 46 });
	die.PushBack({ 264, 0, 44, 46 });
	die.PushBack({ 308, 0, 44, 46 });
	die.speed = 0.2f;
	die.loop = false;

	//laser 360º
	move_360.PushBack({ 125, 81, 23, 33 });  //-- left
	move_360.PushBack({ 185, 79, 24, 35 }); //-- left-up
	move_360.PushBack({ 224, 77, 27, 35 }); //-- left-up
	move_360.PushBack({ 263, 77, 26, 35 }); //-- left-up
	move_360.PushBack({ 298, 76, 28, 35 });  //-- up
	move_360.PushBack({ 300, 122, 28, 36 });  //-- right-up
	move_360.PushBack({ 265, 123, 25, 35 });  //-- right-up
	move_360.PushBack({ 229, 123, 21, 36 });  //-- right-up
	move_360.PushBack({ 188, 124, 24, 35 });  //-- right
	move_360.PushBack({ 125, 124, 26, 35 });  //-- right-down
	move_360.PushBack({ 89, 126, 27, 35 });  //-- right-down
	move_360.PushBack({ 52, 126, 29, 34 });  //-- right-down
	move_360.PushBack({ 17, 125, 28, 35 });  //-- down
	move_360.PushBack({ 19, 81, 26, 35 });  //-- left-down
	move_360.PushBack({ 54, 80, 27, 36 });  //-- left-down
	move_360.PushBack({ 90, 81, 26, 35 });  //-- left-down
	move_360.speed = 0.6f;
	move_360.SetInitialFrame(DOWN);

}

ModuleGreenBasic::~ModuleGreenBasic()
{}

// Load assets
bool ModuleGreenBasic::Start()
{
	LOG("Loading basic green enemy textures");
	basic_green_tex = App->textures->Load("OutZone/Sprites/Enemies/Level 1/Soldier Green.png");
	basic_green_dead_tex = App->textures->Load("OutZone/Sprites/Enemies/Enemies Common Dead/common dead sprites.png");
	current_animation = &down;
	bool ret = true;
	weapon_anim = &move_360;
	direction = DOWN;
	laser_p0 = &App->particles->basic_laser_p0;
	shoot_start = &App->particles->shoot_start;
	laser_end = &App->particles->laser_end;
	ResetPosition();

	GreenBasicCollider = App->collisions->AddCollider({ 0, 0, 20, 30 }, COLLIDER_ENEMY, this);

	return ret;
}

bool ModuleGreenBasic::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;
	die.Reset();

	App->textures->Unload(basic_green_tex);
	App->textures->Unload(basic_green_dead_tex);

	return true;
}

// Update: draw background
update_status ModuleGreenBasic::Update()
{
	PreviousPos = position;
	int speed = 2;
	now = SDL_GetTicks();

	if (!dead){
		position.y += speed;

		if (direction != IDLE){
			if (CheckPJAnimPos(weapon_anim, direction))
				App->render->Blit(basic_green_tex, position.x, position.y, &(current_animation->GetCurrentFrame()));
			else App->render->Blit(basic_green_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));
		}
		else App->render->Blit(basic_green_tex, position.x, position.y, &(weapon_anim->GetActualFrame()));
	}
	else{
		App->render->Blit(basic_green_dead_tex, position.x-5, position.y-5, &(current_animation->GetCurrentFrame()));
		if (die.Finished()){
			this->Disable();
		}
	}
	

	GreenBasicCollider->SetPos(position.x+5, position.y);
	return UPDATE_CONTINUE;
}

bool ModuleGreenBasic::CheckPJAnimPos(Animation* anim, Direction dest_anim){

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
		case ANGLE_150: if (FrameIndex >= ANGLE_330)
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

void ModuleGreenBasic::CreateShoot(Animation* anim)const{

	uint FrameIndex = (uint)anim->GetFrameIndex();
		switch (FrameIndex)
		{
		case LEFT:
			App->particles->SetParticleSpeed(laser_p0, -5, 0);
			App->particles->SetColliderCorrection(laser_p0, -6, 6);
			App->particles->AddParticle(*laser_p0, position.x - 8, position.y + 1, laser_p0->collider, laserbox_p0, -90);
			App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 1, shoot_start->collider, nullrect, -90);
			break;
		case ANGLE_60:
			App->particles->SetParticleSpeed(laser_p0, -4.61f, -1.91f);
			App->particles->SetColliderCorrection(laser_p0, -5, 4);
			App->particles->AddParticle(*laser_p0, position.x, position.y - 5, laser_p0->collider, laserbox_p0, -67.5);
			App->particles->AddParticle(*shoot_start, position.x - 5, position.y - 5, shoot_start->collider, nullrect, -67.5);
			break;
		case LEFT_UP:
			App->particles->SetParticleSpeed(laser_p0, -3.53f, -3.53f);
			App->particles->SetColliderCorrection(laser_p0, -4, 2);
			App->particles->AddParticle(*laser_p0, position.x + 3, position.y - 12, laser_p0->collider, laserbox_p0, -45);
			App->particles->AddParticle(*shoot_start, position.x - 2, position.y - 12, shoot_start->collider, nullrect, -45);
			break;
		case ANGLE_30:
			App->particles->SetParticleSpeed(laser_p0, -1.91f, -4.61f);
			App->particles->SetColliderCorrection(laser_p0, -2, 1);
			App->particles->AddParticle(*laser_p0, position.x + 8, position.y - 12, laser_p0->collider, laserbox_p0, -22.5);
			App->particles->AddParticle(*shoot_start, position.x + 3, position.y - 12, shoot_start->collider, nullrect, -22.5);
			break;
		case UP:
			App->particles->SetParticleSpeed(laser_p0, 0, -5);
			App->particles->SetColliderCorrection(laser_p0, 0, 0);
			App->particles->AddParticle(*laser_p0, position.x + 21, position.y - 15, laser_p0->collider, laserbox_p0);
			App->particles->AddParticle(*shoot_start, position.x + 15, position.y - 15, shoot_start->collider, nullrect);
			break;
		case ANGLE_330:
			App->particles->SetParticleSpeed(laser_p0, 1.91f, -4.61f);
			App->particles->SetColliderCorrection(laser_p0, 1, 0);
			App->particles->AddParticle(*laser_p0, position.x + 25, position.y - 12, laser_p0->collider, laserbox_p0, 12.5);
			App->particles->AddParticle(*shoot_start, position.x + 20, position.y - 12, shoot_start->collider, nullrect, 12.5);
			break;
		case RIGHT_UP:
			App->particles->SetParticleSpeed(laser_p0, 3.53f, -3.53f);
			App->particles->SetColliderCorrection(laser_p0, 4, 2);
			App->particles->AddParticle(*laser_p0, position.x + 30, position.y - 12, laser_p0->collider, laserbox_p0, 45);
			App->particles->AddParticle(*shoot_start, position.x + 25, position.y - 12, shoot_start->collider, nullrect, 45);
			break;
		case ANGLE_300:
			App->particles->SetParticleSpeed(laser_p0, 4.61f, -1.91f);
			App->particles->SetColliderCorrection(laser_p0, 5, 4);
			App->particles->AddParticle(*laser_p0, position.x + 33, position.y - 5, laser_p0->collider, laserbox_p0, 67.5);
			App->particles->AddParticle(*shoot_start, position.x + 28, position.y - 5, shoot_start->collider, nullrect, 67.5);
			break;
		case RIGHT:
			App->particles->SetParticleSpeed(laser_p0, 5, 0);
			App->particles->SetColliderCorrection(laser_p0, 6, 6);
			App->particles->AddParticle(*laser_p0, position.x + 35, position.y + 2, laser_p0->collider, laserbox_p0, 90);
			App->particles->AddParticle(*shoot_start, position.x + 30, position.y + 2, shoot_start->collider, nullrect, 90);
			break;
		case ANGLE_240:
			App->particles->SetParticleSpeed(laser_p0, 4.61f, 1.91f);
			App->particles->SetColliderCorrection(laser_p0, 6, 7);
			App->particles->AddParticle(*laser_p0, position.x + 25, position.y + 15, laser_p0->collider, laserbox_p0, 102.5);
			App->particles->AddParticle(*shoot_start, position.x + 20, position.y + 15, shoot_start->collider, nullrect, 102.5);
			break;
		case RIGHT_DOWN:
			App->particles->SetParticleSpeed(laser_p0, 3.53f, 3.53f);
			App->particles->SetColliderCorrection(laser_p0, 4, 10);
			App->particles->AddParticle(*laser_p0, position.x + 20, position.y + 17, laser_p0->collider, laserbox_p0, 135);
			App->particles->AddParticle(*shoot_start, position.x + 18, position.y + 19, shoot_start->collider, nullrect, 135);
			break;
		case ANGLE_210:
			App->particles->SetParticleSpeed(laser_p0, +1.91f, +4.61f);
			App->particles->SetColliderCorrection(laser_p0, 1, 12);
			App->particles->AddParticle(*laser_p0, position.x + 18, position.y + 17, laser_p0->collider, laserbox_p0, 167.5);
			App->particles->AddParticle(*shoot_start, position.x + 15, position.y + 21, shoot_start->collider, nullrect, 167.5);
			break;
		case DOWN:
			App->particles->SetParticleSpeed(laser_p0, 0, 5);
			App->particles->SetColliderCorrection(laser_p0, 0, 12);
			App->particles->AddParticle(*laser_p0, position.x + 8, position.y + 20, laser_p0->collider, laserbox_p0, 180);
			App->particles->AddParticle(*shoot_start, position.x + 3, position.y + 27, shoot_start->collider, nullrect, 180);
			break;
		case ANGLE_150:
			App->particles->SetParticleSpeed(laser_p0, -1.91f, 4.61f);
			App->particles->SetColliderCorrection(laser_p0, -2, 12);
			App->particles->AddParticle(*laser_p0, position.x, position.y + 20, laser_p0->collider, laserbox_p0, -157.5);
			App->particles->AddParticle(*shoot_start, position.x - 5, position.y + 20, shoot_start->collider, nullrect, -157.5);
			break;
		case LEFT_DOWN:
			App->particles->SetParticleSpeed(laser_p0, -3.53f, 3.53f);
			App->particles->SetColliderCorrection(laser_p0, -5, 10);
			App->particles->AddParticle(*laser_p0, position.x - 5, position.y + 17, laser_p0->collider, laserbox_p0, -125);
			App->particles->AddParticle(*shoot_start, position.x - 11, position.y + 17, shoot_start->collider, nullrect, -135);
			break;
		case ANGLE_120:
			App->particles->SetParticleSpeed(laser_p0, -4.61f, 1.91f);
			App->particles->SetColliderCorrection(laser_p0, -6, 8);
			App->particles->AddParticle(*laser_p0, position.x - 5, position.y + 13, laser_p0->collider, laserbox_p0, -102.5);
			App->particles->AddParticle(*shoot_start, position.x - 13, position.y + 13, shoot_start->collider, nullrect, -107.5);
			break;
		default:
			break;
		}
}

Animation* ModuleGreenBasic::SelectAnimation(Direction direction){

	Animation* ret = current_animation;
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

	return ret;
}

void ModuleGreenBasic::ResetPosition(){
	position.x = 120;
	position.y = 14000;
}

void ModuleGreenBasic::OnCollision(Collider* c1, Collider* c2) {
	if (GreenBasicCollider == c1 && GreenBasicCollider != nullptr){
		if (c2->type == COLLIDER_WALL || c2->type == COLLIDER_PASS_BULLET){
			position = PreviousPos;
		}
		if (c2->type == COLLIDER_PLAYER_SHOT){
			dead = true;
			current_animation = &die;
			GreenBasicCollider->to_delete = true;
		}
	}
}