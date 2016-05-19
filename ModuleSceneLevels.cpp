#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "ModuleScoreScreen.h"
#include "ModuleLevelsTop.h"
#include "ModuleUI.h"
#include "SDL/include/SDL_timer.h"

ModuleSceneLevels::ModuleSceneLevels()
{
	// level4
	level4.x = 0;
	level4.y = 0;
	level4.w = 240;
	level4.h = 7519;
	//Platform
	platform_anim.PushBack({ 0, 0, 77, 64 });
	platform_p.PushBack({ 0.5f, 0 }, 100, &platform_anim);
	platform_p.loop = true;

	platform1_pos.x = -100;
	platform1_pos.y = 4383;

	platform2_pos.x = SCREEN_WIDTH+100;
	platform2_pos.y = 4222;

	platform3_pos.x = -100;
	platform3_pos.y = 3870;

	//Sub-Lights
	sublightanim.PushBack({ 0, 0, 256, 666 });
	sublightanim.PushBack({ 256, 0, 256, 666 });
	sublightanim.speed = 0.06f;
	//Lights

	lights.PushBack({ 0, 0, 256, 578 });
	lights.PushBack({ 256, 0, 256, 578 });
	lights.speed = 0.03f;
	// Lava
	lavaanim.PushBack({ 0, 0, 256, 830 });
	lavaanim.PushBack({ 256, 0, 256, 830 });
	lavaanim.PushBack({ 512, 0, 256, 830 });
	lavaanim.speed = 0.01f;
	
	
}

// CAMERA RESET FUNCTION
bool ModuleSceneLevels::CameraReset(){
	return true;
}

ModuleSceneLevels::~ModuleSceneLevels()
{}

// Load assets

bool ModuleSceneLevels::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	App->current_level = this;

	on_bg = App->textures->Load("OutZone/Sprites/Map/OnLightsAnim.png");
	lava = App->textures->Load("OutZone/Sprites/Map/lava_anim.png");
	sublighttex = App->textures->Load("OutZone/Sprites/Map/sublights.png");
	graphics_l4 = App->textures->Load("OutZone/Sprites/Map/level4.png");
	graphics_l4_below = App->textures->Load("OutZone/Sprites/Map/level4_below.png");
	platform_t = App->textures->Load("Outzone/Sprites/Map/MovingPlatform.png");

	level4_song = App->audio->LoadMusic("OutZone/Sounds/Music/level4.ogg");

	App->audio->PlayMusic(level4_song, LOOP);

	//Enable Player and Collisions
	App->player->Enable();
	App->collisions->Enable();
	App->levelstop->Enable();
	App->enemies->Enable();
	App->particles->Enable();

	App->ui->game = true;
	App->ui->SetGameStartConditions();
	App->ui->e_timer = SDL_GetTicks()+1000;


	////Level2 boss
	//App->collisions->AddCollider({ 0, 6254, 92, 180 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 150, 6254, 92, 180 }, COLLIDER_WALL);
	////Level3 lava
	//App->collisions->AddCollider({ 0, 5604, 42, 318 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 42, 5703, 27, 119 }, COLLIDER_HOLE);
	////Level3 lava
	//App->collisions->AddCollider({ 0, 5203, 75, 156 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 75, 5271, 32, 88 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 53, 5359, 52, 94 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 107, 5325, 33, 96 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 140, 5356, 21, 63 }, COLLIDER_HOLE);
	////Levek3 lava
	//App->collisions->AddCollider({ 181, 5176, 32, 58 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 212, 5144, 30, 149 }, COLLIDER_HOLE);
	////Level3 wall(lassers)
	//App->collisions->AddCollider({ 0, 4705, 66, 93 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 190, 4705, 66, 93 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 0, 4318, 16, 388 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 223, 4318, 16, 388 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 0, 4225, 66, 93 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 193, 4225, 66, 93 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 29, 3874, 35, 62 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 64, 3874, 33, 93 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 97, 3874, 30, 126 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 127, 3908, 67, 59 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 3746, 32, 97 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 32, 3746, 32, 62 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 129, 3746, 32, 95 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 162, 3746, 32, 59 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 189, 3714, 32, 126 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 222, 3714, 32, 158 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 3650, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 64, 3585, 32, 62 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 96, 3585, 32, 127 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 127, 3555, 32, 93 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 190, 3586, 32, 62 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 222, 3586, 32, 94 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 3427, 32, 157 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 32, 3457, 32, 95 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 64, 3489, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 160, 3458, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 192, 3458, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 224, 3425, 32, 128 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 64, 3361, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 96, 3361, 32, 96 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 128, 3361, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 191, 3329, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 223, 3329, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 2576, 32, 145 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 32, 2609, 32, 77 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 128, 2609, 32, 77 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 160, 2593, 32, 127 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 192, 2593, 32, 127 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 224, 2609, 32, 77 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 63, 2481, 32, 80 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 66, 2372, 87, 59 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 104, 2431, 47, 129 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 65, 2482, 127, 79 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 98, 2450, 61, 32 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 159, 2481, 32, 80 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 2433, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 223, 2466, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 192, 2351, 32, 81 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 224, 2351, 32, 81 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 2271, 32, 96 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 32, 2271, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 127, 2273, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 190, 2241, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 222, 2241, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 63, 2081, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 95, 2081, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 190, 2081, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 222, 2050, 32, 96 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 2017, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 96, 1921, 32, 129 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 128, 1921, 32, 129 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 160, 1969, 32, 80 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 1890, 32, 96 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 32, 1921, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 224, 1921, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 96, 1825, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 160, 1809, 32, 81 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 192, 1809, 32, 81 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 224, 1809, 32, 81 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 1728, 32, 98 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 32, 1713, 32, 146 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 64, 1713, 32, 81 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 96, 1713, 32, 81 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 192, 1697, 32, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 224, 1697, 32, 64 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 0, 1345, 63, 62 }, COLLIDER_WALL);
	////Level3 walls
	//App->collisions->AddCollider({ 175, 1345, 63, 62 }, COLLIDER_WALL);
	////Level3 hole
	//App->collisions->AddCollider({ 0, 1187, 64, 125 }, COLLIDER_HOLE);
	////Level3 hole
	//App->collisions->AddCollider({ 112, 1058, 65, 62 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 177, 1058, 30, 254 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 207, 993, 50, 319 }, COLLIDER_HOLE);
	////Level3 hole
	//App->collisions->AddCollider({ 0, 640, 32, 480 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 32, 707, 32, 286 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 64, 707, 32, 61 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 64, 864, 32, 128 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 96, 928, 32, 64 }, COLLIDER_HOLE);
	////Level3 hole
	//App->collisions->AddCollider({ 143, 708, 32, 60 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 175, 708, 32, 187 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 207, 642, 32, 284 }, COLLIDER_HOLE);
	////Level3 boss left
	//App->collisions->AddCollider({ 0, 365, 15, 147 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 15, 380, 15, 132 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 30, 395, 15, 117 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 45, 410, 15, 102 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 60, 425, 15, 87 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 75, 440, 15, 72 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 90, 455, 15, 57 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 105, 470, 15, 42 }, COLLIDER_HOLE_BOSS_LEFT);
	//App->collisions->AddCollider({ 120, 485, 7, 27 }, COLLIDER_HOLE_BOSS_LEFT);
	////Level3 boss right
	//App->collisions->AddCollider({ 127, 480, 30, 32 }, COLLIDER_HOLE_BOSS_RIGHT);
	//App->collisions->AddCollider({ 157, 467, 30, 45 }, COLLIDER_HOLE_BOSS_RIGHT);
	//App->collisions->AddCollider({ 187, 452, 30, 60 }, COLLIDER_HOLE_BOSS_RIGHT);
	//App->collisions->AddCollider({ 217, 440, 30, 72 }, COLLIDER_HOLE_BOSS_RIGHT);


	////Level 1 start
	//App->collisions->AddCollider({ 0, 14893, 98, 212 }, COLLIDER_WALL);//LEFT
	//App->collisions->AddCollider({ 0, 14873, 75, 20 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 160, 14907, 96, 87 }, COLLIDER_WALL);//RIGHT
	//App->collisions->AddCollider({ 178, 14993, 78, 30 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 195, 15023, 61, 17 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 226, 15040, 30, 19 }, COLLIDER_WALL);
	////level 1 rocks

	//App->collisions->AddCollider({ 129, 14357, 31, 38 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 192, 14293, 31, 38 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 1, 14164, 30, 38 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 162, 14001, 31, 38 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 66, 13328, 29, 38 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 193, 13297, 31, 38 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 0, 13265, 32, 38 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 95, 13171, 33, 38 }, COLLIDER_WALL);
	////Level 1 more walls
	//App->collisions->AddCollider({ 0, 13700, 123, 145 }, COLLIDER_PASS_BULLET);
	//App->collisions->AddCollider({ 0, 13843, 32, 35 }, COLLIDER_PASS_BULLET);
	//App->collisions->AddCollider({ 198, 13699, 58, 143 }, COLLIDER_PASS_BULLET);
	//App->collisions->AddCollider({ 0, 13414, 61, 141 }, COLLIDER_PASS_BULLET);
	//App->collisions->AddCollider({ 136, 13410, 120, 146 }, COLLIDER_PASS_BULLET);

	//App->collisions->AddCollider({ 0, 11925, 95, 82 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 163, 11925, 93, 79 }, COLLIDER_WALL);
	////level 2 walls
	//App->collisions->AddCollider({ 163, 11040, 93, 97 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 0, 10550, 94, 73 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 161, 10552, 95, 73 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 0, 9283, 97, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 161, 9284, 95, 63 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 0, 9154, 33, 64 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 97, 9178, 159, 41 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 87, 9007, 84, 171 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 64, 8641, 34, 132 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 161, 8641, 31, 131 }, COLLIDER_WALL);

	//App->collisions->AddCollider({ 0, 8458, 75, 126 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 182, 8465, 74, 118 }, COLLIDER_WALL);
	////level 2 holes
	//App->collisions->AddCollider({ 0, 10086, 68, 200 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 10285, 48, 22 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 189, 10090, 66, 196 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 207, 10286, 49, 19 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 73, 9959, 94, 58 }, COLLIDER_HOLE);

	//App->collisions->AddCollider({ 171, 9799, 28, 90 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 197, 9831, 59, 56 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 44, 9767, 58, 121 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 9830, 44, 58 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 108, 9639, 132, 56 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 168, 9695, 67, 33 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 9640, 37, 57 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 9447, 38, 121 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 106, 9448, 29, 121 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 202, 9447, 55, 121 }, COLLIDER_HOLE);

	//App->collisions->AddCollider({ 202, 7557, 54, 59 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 74, 7528, 59, 88 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 7527, 36, 89 }, COLLIDER_HOLE);

	//App->collisions->AddCollider({ 202, 7398, 54, 90 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 75, 7364, 61, 93 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 138, 7396, 30, 93 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 7205, 42, 91 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 43, 7176, 27, 153 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 71, 7237, 34, 60 }, COLLIDER_HOLE);

	//App->collisions->AddCollider({ 107, 7207, 26, 89 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 174, 7078, 82, 155 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 135, 7110, 39, 58 }, COLLIDER_HOLE);

	//App->collisions->AddCollider({ 108, 7078, 27, 90 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 7079, 70, 57 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 0, 6917, 69, 59 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 46, 6953, 87, 55 }, COLLIDER_HOLE);
	//App->collisions->AddCollider({ 107, 6888, 27, 120 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 0, 2430, 65, 1228 }, COLLIDER_HOLE);
	App->collisions->AddCollider({ 175, 2493, 65, 1162 }, COLLIDER_HOLE);

	App->collisions->AddCollider({ 0, 2089, 33, 54 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 64, 2087, 62, 56 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 1863, 63, 55 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 32, 1990, 65, 56 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 190, 1832, 50, 54 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 1412, 161, 58 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 1470, 33, 63 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 223, 1257, 17, 276}, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 1290, 97, 53 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 159, 1257, 66, 53 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 64, 1226, 32, 103 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 64, 1029, 32, 121 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 94, 1092, 67, 58 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 159, 1029, 32, 121 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 933, 97, 56 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 63, 873, 33, 100 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 159, 873, 31, 119 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 189, 936, 51, 54 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 224, 772, 16, 58 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 63, 773, 130, 57 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 0, 774, 32, 55 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 548, 64, 123 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 191, 552, 49, 119 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 7198, 46, 80 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 193, 7198, 46, 80 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 6795, 64, 51 }, COLLIDER_WALL);
	App->collisions->AddCollider({ 160, 6795, 80, 51 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 133, 6560, 120, 30 }, COLLIDER_WALL);	 //Same kind of structure
	App->collisions->AddCollider({ 134, 6439, 120, 30 }, COLLIDER_WALL);	 //Same kind of structure
	App->collisions->AddCollider({ 137, 6439, 20, 130 }, COLLIDER_WALL);	 //Same kind of structure
																			
	App->collisions->AddCollider({ 133, 6560-223, 120, 30 }, COLLIDER_WALL); //Same kind of structure
	App->collisions->AddCollider({ 134, 6439-223, 120, 30 }, COLLIDER_WALL); //Same kind of structure
	App->collisions->AddCollider({ 137, 6439-223, 20, 130 }, COLLIDER_WALL); //Same kind of structure
																	
	App->collisions->AddCollider({ 202, 6560-449, 120, 30 }, COLLIDER_WALL); //Same kind of structure
	App->collisions->AddCollider({ 202, 6439-449, 120, 30 }, COLLIDER_WALL); //Same kind of structure
	App->collisions->AddCollider({ 202, 6439-449, 20, 130 }, COLLIDER_WALL); //Same kind of structure
																			
	App->collisions->AddCollider({ 0, 6560 - 449, 90, 30 }, COLLIDER_WALL);	 //Same kind of structure
	App->collisions->AddCollider({ 0, 6439 - 449, 90, 30 }, COLLIDER_WALL);	 //Same kind of structure
	App->collisions->AddCollider({ 66, 6439 - 449, 20, 130 }, COLLIDER_WALL);//Same kind of structure

	App->collisions->AddCollider({ 0, 4901, 63, 122 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 192, 4803, 63, 124 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 0, 4704, 63, 127 }, COLLIDER_WALL);

	App->collisions->AddCollider({ 193, 4640, 48, 55 }, COLLIDER_WALL);

	App->render->camera.y = -7199*SCREEN_SIZE;

	CameraReset();

	//App->enemies->AddEnemy(BIGTURRET, 0, 13742);
	//App->enemies->AddEnemy(BIGTURRET, 160, 13458);

	App->enemies->AddEnemy(BOSS, 88, -5);
	App->enemies->AddEnemy(SMALLTURRET, 5, 2759);
	App->enemies->AddEnemy(SMALLTURRET, 5, 2792);
	App->enemies->AddEnemy(SMALLTURRET, 5, 2825);
	App->enemies->AddEnemy(SMALLTURRET, 5, 3112);
	App->enemies->AddEnemy(SMALLTURRET, 5, 3149);
	App->enemies->AddEnemy(SMALLTURRET, 5, 3189);
	App->enemies->AddEnemy(SMALLTURRET, 222, 2988);
	App->enemies->AddEnemy(SMALLTURRET, 222, 2951);
	App->enemies->AddEnemy(SMALLTURRET, 222, 3025);
	//App->enemies->AddEnemy(SMALLTURRET, 100, 12946);
	//App->enemies->AddEnemy(SMALLTURRET, 158, 12953);
	//App->enemies->AddEnemy(SMALLTURRET, 4, 12909);
	//App->enemies->AddEnemy(SMALLTURRET, 74, 12904);
	//App->enemies->AddEnemy(SMALLTURRET, 138, 12895);
	//App->enemies->AddEnemy(SMALLTURRET, 200, 12918);
	//App->enemies->AddEnemy(SMALLTURRET, 7, 14480);
	//App->enemies->AddEnemy(SMALLTURRET, 134, 14064);

	//App->enemies->AddEnemy(TRUCK, 24, 14188);

	////ENEMIES PATHS

	//gb1.PushBack({ 0, 1 }, 140);
	//gb1.PushBack({ 1, 1 }, 300);
	//gb1.loop = false;

	//gb2.PushBack({ 0, 1 }, 150);
	//gb2.PushBack({ 1, 1 }, 110);
	//gb2.PushBack({ 1, 0 }, 60);
	//gb2.loop = false;

	//gb3.PushBack({ 0, 1 }, 140);
	//gb3.PushBack({ 1, 1 }, 300);
	//gb3.loop = false;

	//gb4.PushBack({ 0, 1 }, 200);

	//gb5.PushBack({ 0, 1 }, 200);

	//gb6.PushBack({ 0, 1 }, 200);

	//gb7.PushBack({ 0, 1 }, 200);

	//gb8.PushBack({ 0, 1 }, 90);
	//gb8.PushBack({ 1, 1 }, 90);
	//gb8.PushBack({ 1, 0 }, 90);

	//gb9.PushBack({ 0, 1 }, 90);
	//gb9.PushBack({ 1, 1 }, 90);
	//gb9.PushBack({ 1, 0 }, 90);

	//gb10.PushBack({ 0, 1 }, 90);
	//gb10.PushBack({ 1, 1 }, 90);
	//gb10.PushBack({ 1, 0 }, 90);

	//gb11.PushBack({ 0, 1 }, 90);
	//gb11.PushBack({ 1, 1 }, 90);
	//gb11.PushBack({ 1, 0 }, 110);

	//gb12.PushBack({ 0, 1 }, 90);
	//gb12.PushBack({ 1, 1 }, 90);
	//gb12.PushBack({ 1, 0 }, 110);

	//gb13.PushBack({ 0, 1 }, 90);
	//gb13.PushBack({ 1, 1 }, 90);
	//gb13.PushBack({ 1, 0 }, 110);

	//gb14.PushBack({ 0, 0 }, 500000);

	//gb15.PushBack({ 0, 1 }, 90);
	//gb15.PushBack({ -1, 1 }, 90);
	//gb15.PushBack({ -1, 0 }, 110);

	//gb16.PushBack({ 0, 1 }, 90);
	//gb16.PushBack({ -1, 1 }, 90);
	//gb16.PushBack({ -1, 0 }, 110);

	//gb17.PushBack({ 0, 1 }, 90);
	//gb17.PushBack({ -1, 1 }, 90);
	//gb17.PushBack({ -1, 0 }, 110);

	//gb18.PushBack({ 0, 1 }, 90);
	//gb18.PushBack({ -1, 1 }, 90);
	//gb18.PushBack({ -1, 0 }, 110);

	//gb19.PushBack({ 0, 1 }, 90);
	//gb19.PushBack({ -1, 1 }, 90);
	//gb19.PushBack({ -1, 0 }, 110);

	//gb20.PushBack({ 0, 1 }, 90);
	//gb20.PushBack({ -1, 1 }, 90);
	//gb20.PushBack({ -1, 0 }, 110);

	//App->enemies->AddEnemy(GREENBASIC, 140, 14980, &gb1);
	//App->enemies->AddEnemy(GREENBASIC, 100, 14922, &gb2);
	//App->enemies->AddEnemy(GREENBASIC, 140, 14876, &gb3);
	//App->enemies->AddEnemy(GREENBASIC, 100, 14850, &gb4);
	//App->enemies->AddEnemy(GREENBASIC, 140, 14800, &gb5);
	//App->enemies->AddEnemy(GREENBASIC, 120, 14760, &gb6);
	//App->enemies->AddEnemy(GREENBASIC, 100, 14710, &gb7);
	//App->enemies->AddEnemy(GREENBASIC, 100, 14660, &gb8);
	//App->enemies->AddEnemy(GREENBASIC, 100, 14645, &gb9);
	//App->enemies->AddEnemy(GREENBASIC, 130, 14660, &gb10);
	//App->enemies->AddEnemy(GREENBASIC, 50, 14610, &gb11);
	//App->enemies->AddEnemy(GREENBASIC, 50, 14595, &gb12);
	//App->enemies->AddEnemy(GREENBASIC, 80, 14610, &gb13);
	//App->enemies->AddEnemy(GREENBASIC, 30, 14610, &gb14);
	//App->enemies->AddEnemy(GREENBASIC, 60, 14570, &gb15);
	//App->enemies->AddEnemy(GREENBASIC, 90, 14570, &gb16);
	//App->enemies->AddEnemy(GREENBASIC, 90, 14555, &gb17);
	//App->enemies->AddEnemy(GREENBASIC, 90, 14520, &gb18);
	//App->enemies->AddEnemy(GREENBASIC, 120, 14520, &gb19);
	//App->enemies->AddEnemy(GREENBASIC, 120, 14505, &gb20);

	return ret;
}

// Load assets
bool ModuleSceneLevels::CleanUp()
{
	LOG("Unloading Levels stage");

	// Unload textures
	App->textures->Unload(graphics_l4);
	App->textures->Unload(on_bg);
	App->textures->Unload(lava);
	App->textures->Unload(sublighttex);

	//Disable player
	App->player->Disable();
	App->ui->game = false;
	//Disable Collisions
	App->collisions->Disable();
	
	App->particles->Disable();
	App->levelstop->Disable();
	App->enemies->Disable();

	//Stop audio
	App->audio->StopAudio();
	App->audio->UnloadMusic(level4_song);

	App->render->camera.y = 0;

	//restart paths
	//RestartEnemiesPaths();

	return true;
}

// Update: draw background
update_status ModuleSceneLevels::Update()
{
	// Map movement

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->fade->FadeToBlack(this, (Module*)App->losescreen, 1.0f);
	}
	if (App->render->camera.y > -1){
		App->fade->FadeToBlack(this, (Module*)App->winscreen, 0.3f);
	}
	// Draw everything --------------------------------------
	if (App->ui->game){
	/*	App->render->Blit(lava, 0, 0, &lavaanim.GetCurrentFrame());
		App->render->Blit(lava, 0, 830, &lavaanim.GetCurrentFrame());
		App->render->Blit(lava, 0, 2896, &lavaanim.GetCurrentFrame());
		App->render->Blit(lava, 0, 5156, &lavaanim.GetCurrentFrame());*/

		//App->render->Blit(sublighttex, 0, 6781, &sublightanim.GetCurrentFrame());
		App->render->Blit(graphics_l4_below, 0, 0, &level4);
		App->render->Blit(graphics_l4, 0, 0, &level4); // Map
		//App->render->Blit(on_bg, 0, 8445, &lights.GetCurrentFrame());
		platform1_aux_pos = platform1_pos + platform_p.GetCurrentSpeed();
		App->render->Blit(platform_t, platform1_aux_pos.x , platform1_aux_pos.y, &platform_anim.GetCurrentFrame());

		if (platform1_aux_pos.x > SCREEN_WIDTH+150) platform_p.Restart();

		platform2_aux_pos = platform2_pos - platform_p.GetCurrentSpeed();
		App->render->Blit(platform_t, platform2_aux_pos.x, platform2_aux_pos.y, &platform_anim.GetCurrentFrame());

		if (platform2_aux_pos.x < -150) platform_p.Restart();

		platform3_aux_pos = platform3_pos + platform_p.GetCurrentSpeed();
		App->render->Blit(platform_t, platform3_aux_pos.x, platform3_aux_pos.y, &platform_anim.GetCurrentFrame());

		if (platform3_aux_pos.x > SCREEN_WIDTH + 150) platform_p.Restart();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneLevels::RestartEnemiesPaths(){
	gb1.Restart();
	gb2.Restart();
	gb3.Restart();
	gb4.Restart();
	gb5.Restart();
	gb6.Restart();
	gb7.Restart();
	gb8.Restart();
	gb9.Restart();
	gb10.Restart();
	gb11.Restart();
	gb12.Restart();
	gb13.Restart();
	gb14.Restart();
	gb15.Restart();
	gb16.Restart();
	gb17.Restart();
	gb18.Restart();
	gb19.Restart();
	gb20.Restart();
}