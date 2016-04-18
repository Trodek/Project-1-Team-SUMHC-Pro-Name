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

	//// LASER ANIMATIONS

	/*//Char Up anim
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
	left.speed = 0.25f;*/

	//char down
	down.PushBack({ 19, 311, 27, 35 });
	down.PushBack({ 57, 314, 27, 32 });
	down.PushBack({ 95, 313, 32, 33 });
	down.PushBack({ 134, 315, 27, 31 });
	down.speed = 0.2f;

	/*//char left-up
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

	// char die
	
	fall_hole.speed = 0.1f;
	fall_hole.loop = false;

	//laser 360º
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
	laser_360.PushBack({ 18, 139, 27, 37 });  //-- right-down*/
	laser_360.PushBack({ 19, 311, 27, 35 });  //-- down
	/*laser_360.PushBack({ 19, 90, 31, 39 });  //-- left-down
	laser_360.PushBack({ 19, 90, 31, 39 });  //-- left-down
	laser_360.PushBack({ 19, 90, 31, 39 });  //-- left-down*/
	laser_360.speed = 0.6f;
	laser_360.SetInitialFrame(DOWN);

}

ModuleGreenBasic::~ModuleGreenBasic()
{}

// Load assets
bool ModuleGreenBasic::Start()
{
	LOG("Loading player textures");
	basic_green_tex = App->textures->Load("Sprites\Enemies\Level 1\Soldier Green.png");
	current_animation = &up;
	bool ret = true;
	weapon_anim = &laser_360;
	direction = IDLE;
	laser_p0 = &App->particles->basic_laser_p0;
	shoot_start = &App->particles->shoot_start;
	laser_end = &App->particles->laser_end;
	ResetPosition();

	GreenBasicCollider = App->collisions->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, this);

	return ret;
}

bool ModuleGreenBasic::CleanUp(){

	LOG("Player CleanUp--------");

	dead = false;
	fall_hole.Reset();

	App->textures->Unload(basic_green_tex);

	return true;
}

// Update: draw background
update_status ModuleGreenBasic::Update()
{
	PreviousPos = position;
	int speed = 2;
	now = SDL_GetTicks();

	LOG("Camera.y = %d.", App->render->camera.y);

	if (!dead){
	}

	GreenBasicCollider->SetPos(position.x + 10, position.y + 20);


	return UPDATE_CONTINUE;
}

bool ModuleGreenBasic::CheckPJAnimPos(Animation* anim, EnemyDirection dest_anim){

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

Animation* ModuleGreenBasic::SelectAnimation(EnemyDirection direction){

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
	position.x = 105;
	position.y = 15308;
}

void ModuleGreenBasic::OnCollision(Collider* c1, Collider* c2) {
	if (GreenBasicCollider == c1 && GreenBasicCollider != nullptr){
		if (c2->type == COLLIDER_WALL || c2->type == COLLIDER_PASS_BULLET){
			position = PreviousPos;
		}
		if (c2->type == COLLIDER_HOLE){
			dead = true;
			current_animation = &fall_hole;
		}
	}
}