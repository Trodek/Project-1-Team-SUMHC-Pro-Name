#include "Application.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "EnemyGreenBasic.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"

EnemyGreenBasic::EnemyGreenBasic(int x, int y, ENEMY_TYPES type) : Enemy(x, y, type){

	original = position;

	dir = IDLE;

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

	tex = App->particles->green_basic;

	last_shot = SDL_GetTicks();
}

void EnemyGreenBasic::Move(){

	//Face Player
	float enemy_player_r = position.DistanceTo(App->player->position);
	

	if (path->Moving()){

	}
	else dir = IDLE;

}

void EnemyGreenBasic::Draw(){

}

void EnemyGreenBasic::Shot(){

}