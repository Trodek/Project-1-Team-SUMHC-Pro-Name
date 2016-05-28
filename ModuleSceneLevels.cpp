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


	platform_1_1 = App->collisions->AddCollider({ -SCREEN_WIDTH-123, 4383, SCREEN_WIDTH+177, 64 }, COLLIDER_HOLE);
	platform_1_2 = App->collisions->AddCollider({ -23, 4383, SCREEN_WIDTH+23, 64 }, COLLIDER_HOLE);
																
	platform_2_1 = App->collisions->AddCollider({ SCREEN_WIDTH + 177, 4222, SCREEN_WIDTH+100, 64 }, COLLIDER_HOLE);
	platform_2_2 = App->collisions->AddCollider({ 0, 4222, SCREEN_WIDTH+73, 64 }, COLLIDER_HOLE);
																
	platform_3_1 = App->collisions->AddCollider({ -SCREEN_WIDTH - 123, 3870, SCREEN_WIDTH+177, 64 }, COLLIDER_HOLE);
	platform_3_2 = App->collisions->AddCollider({ -23, 3870, SCREEN_WIDTH+23, 64 }, COLLIDER_HOLE);





	App->render->camera.y = -7199*SCREEN_SIZE;

	CameraReset();

	//App->enemies->AddEnemy(BIGTURRET, 0, 13742);
	//App->enemies->AddEnemy(BIGTURRET, 160, 13458);
	

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


	
	gb2.PushBack({ 0, 1 }, 150);
	gb2.PushBack({ 1, 1 }, 110);
	gb2.PushBack({ 1, 0 }, 60);
	gb2.loop = false;

	gb3.PushBack({ 0, 1 }, 140);
	gb3.PushBack({ 1, 1 }, 300);
	gb3.loop = false;

	gb4.PushBack({ 0, 1 }, 200);

	gb5.PushBack({ 0, 1 }, 200);

	gb6.PushBack({ 0, 1 }, 200);

	gb7.PushBack({ 0, 1 }, 200);

	gb8.PushBack({ 0, 1 }, 90);
	gb8.PushBack({ 1, 1 }, 90);
	gb8.PushBack({ 1, 0 }, 90);

	gb9.PushBack({ 0, 1 }, 90);
	gb9.PushBack({ 1, 1 }, 90);
	gb9.PushBack({ 1, 0 }, 90);

	gb10.PushBack({ 0, 1 }, 90);
	gb10.PushBack({ 1, 1 }, 90);
	gb10.PushBack({ 1, 0 }, 90);

	gb11.PushBack({ 0, 1 }, 90);
	gb11.PushBack({ 1, 1 }, 90);
	gb11.PushBack({ 1, 0 }, 110);

	gb12.PushBack({ 0, 1 }, 90);
	gb12.PushBack({ 1, 1 }, 90);
	gb12.PushBack({ 1, 0 }, 110);

	gb13.PushBack({ 0, 1 }, 90);
	gb13.PushBack({ 1, 1 }, 90);
	gb13.PushBack({ 1, 0 }, 110);

	gb14.PushBack({ 0, 0 }, 500000);

	gb15.PushBack({ 0, 1 }, 90);
	gb15.PushBack({ -1, 1 }, 90);
	gb15.PushBack({ -1, 0 }, 110);

	gb16.PushBack({ 0, 1 }, 90);
	gb16.PushBack({ -1, 1 }, 90);
	gb16.PushBack({ -1, 0 }, 110);

	gb17.PushBack({ 0, 1 }, 90);
	gb17.PushBack({ -1, 1 }, 90);
	gb17.PushBack({ -1, 0 }, 110);

	gb18.PushBack({ 0, 1 }, 90);
	gb18.PushBack({ -1, 1 }, 90);
	gb18.PushBack({ -1, 0 }, 110);

	gb19.PushBack({ 0, 1 }, 90);
	gb19.PushBack({ -1, 1 }, 90);
	gb19.PushBack({ -1, 0 }, 110);

	gb20.PushBack({ 0, 1 }, 90);
	gb20.PushBack({ -1, 1 }, 90);
	gb20.PushBack({ -1, 0 }, 110);

	gb21.PushBack({ 0, 0.5f }, 70);
	gb21.loop = false;

	roomba1.PushBack({ 0, 1 }, 55);
	roomba1.PushBack({ -1, 0 }, 160);
	roomba1.PushBack({ 1, 0 }, 100);
	roomba1.PushBack({ -1, 0 }, 160);
	roomba1.PushBack({ 1, 0 }, 100);
	roomba1.PushBack({ -1, 0 }, 160);
	roomba1.PushBack({ 1, 0 }, 100);
	roomba1.PushBack({ -1, 0 }, 160);
	roomba1.PushBack({ 1, 0 }, 100);
	roomba1.PushBack({ -1, 0 }, 160);
	roomba1.PushBack({ 1, 0 }, 100);
	roomba1.PushBack({ -1, 0 }, 160);

	roomba2.PushBack({ 0, 1 }, 25);
	roomba2.PushBack({ -1, 0 }, 190);
	roomba2.PushBack({ 0, -1 }, 130);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);
	roomba2.PushBack({ 0, 1 }, 90);
	roomba2.PushBack({ 0, -1 }, 90);

	roomba3.PushBack({ 0.5f, 0.5f }, 30);
	roomba3.PushBack({ -0.5f, 0.5f }, 30);
	roomba3.PushBack({ -0.5f, -0.5f }, 30);
	roomba3.PushBack({ 0.5f, -0.5f }, 30);

	sl1.PushBack({ 0, 0 }, 50);
	sl1.PushBack({ 1, 0 }, 125);
	sl1.PushBack({ 0, 0 }, 500);
	sl1.PushBack({ 0, 1 }, 75);
	sl1.PushBack({ -1, 0 }, 555);

	sl2.PushBack({ 0, 0 }, 200);
	sl2.PushBack({ 1, 0 }, 125);
	sl2.PushBack({ 0, 0 }, 500);
	sl2.PushBack({ 0, 1 }, 125);
	sl2.PushBack({ -1, 0 }, 555);

	sl3.PushBack({ 0, 0 }, 50);
	sl3.PushBack({ -1, 0 }, 125);
	sl3.PushBack({ 0, 0 }, 500);
	sl3.PushBack({ 0, 1 }, 75);
	sl3.PushBack({ 1, 0 }, 555);

	sl4.PushBack({ 0, 0 }, 200);
	sl4.PushBack({ -1, 0 }, 125);
	sl4.PushBack({ 0, 0 }, 500);
	sl4.PushBack({ 0, 1 }, 125);
	sl4.PushBack({ 1, 0 }, 555);

	sl5.PushBack({ 0, 0 }, 200);
	sl5.PushBack({ 1, 0 }, 125);
	sl5.PushBack({ 0, 0 }, 500);
	sl5.PushBack({ 0, -1 }, 55);
	sl5.PushBack({ -1, 0 }, 555);

	sl6.PushBack({ 0, 0 }, 50);
	sl6.PushBack({ 1, 0 }, 125);
	sl6.PushBack({ 0, 0 }, 500);
	sl6.PushBack({ 0, -1 }, 105);
	sl6.PushBack({ -1, 0 }, 555);



	RestartEnemies();
	return ret;
}

void ModuleSceneLevels::RestartEnemies() {
	RestartEnemiesPaths();
	if (App->ui->curr_check == 0) {							// y < 7159
		App->enemies->AddEnemy(GREENBASIC, 100, 7100, &gb2);
		App->enemies->AddEnemy(GREENBASIC, 140, 7100, &gb3);
		App->enemies->AddEnemy(GREENBASIC, 100, 7050, &gb4);
		App->enemies->AddEnemy(GREENBASIC, 140, 7140, &gb5);
		App->enemies->AddEnemy(GREENBASIC, 100, 7020, &gb7);
		App->enemies->AddEnemy(GREENBASIC, 130, 7100, &gb10);
		App->enemies->AddEnemy(GREENBASIC, 50, 7150, &gb11);
		App->enemies->AddEnemy(GREENBASIC, 70, 7150, &gb12);
		App->enemies->AddEnemy(GREENBASIC, 80, 7160, &gb13);
		App->enemies->AddEnemy(GREENBASIC, 30, 7160, &gb14);
		
	}
	if (App->ui->curr_check <= 1) {						// y < 7000
		App->enemies->AddEnemy(GREENBASIC, 60, 6780, &gb15);
		App->enemies->AddEnemy(GREENBASIC, 90, 6850, &gb16);
		App->enemies->AddEnemy(GREENBASIC, 90, 6700, &gb17);
		App->enemies->AddEnemy(GREENBASIC, 90, 6600, &gb18);
		App->enemies->AddEnemy(GREENBASIC, 80, 6400, &gb19);
		App->enemies->AddEnemy(GREENBASIC, 80, 6500, &gb20);
	}
	if (App->ui->curr_check <= 2) {					// y < 5965
		App->enemies->AddEnemy(GREENBASIC, 27, 5125, &gb21);
		App->enemies->AddEnemy(GREENBASIC, 198, 5125, &gb21);
		App->enemies->AddEnemy(GREENBASIC, 45, 5000, &gb21);
		App->enemies->AddEnemy(GREENBASIC, 160, 5000, &gb21);

		App->enemies->AddEnemy(GREENBASIC, 27, 5325, &gb19);
		App->enemies->AddEnemy(GREENBASIC, 198, 5325, &gb18);
		App->enemies->AddEnemy(GREENBASIC, 45, 5200, &gb20);
		App->enemies->AddEnemy(GREENBASIC, 160, 5200, &gb4);
		App->enemies->AddEnemy(STRANGE_LARGE, -50, 4950, &sl1);
		App->enemies->AddEnemy(STRANGE_LARGE, -50, 4900, &sl2);
		App->enemies->AddEnemy(STRANGE_LARGE, 196, 4854, &sl3);
		App->enemies->AddEnemy(STRANGE_LARGE, 196, 4804, &sl4);
		App->enemies->AddEnemy(STRANGE_LARGE, -50, 4758, &sl6);
		App->enemies->AddEnemy(STRANGE_LARGE, -50, 4708, &sl5);
	}
	if (App->ui->curr_check <= 3) {				// y < 4900
		App->enemies->AddEnemy(GREENBASIC, 73, 4700, &gb21);
		App->enemies->AddEnemy(GREENBASIC, 140, 4700, &gb21);
		App->enemies->AddEnemy(SMALLTURRET, 5, 2759);
		App->enemies->AddEnemy(SMALLTURRET, 5, 2792);
		App->enemies->AddEnemy(SMALLTURRET, 5, 2825);
		App->enemies->AddEnemy(SMALLTURRET, 5, 3112);
		App->enemies->AddEnemy(SMALLTURRET, 5, 3149);
		App->enemies->AddEnemy(SMALLTURRET, 5, 3189);
		App->enemies->AddEnemy(SMALLTURRET, 222, 2988);
		App->enemies->AddEnemy(SMALLTURRET, 222, 2951);
		App->enemies->AddEnemy(SMALLTURRET, 222, 3025);
	}
	if (App->ui->curr_check <= 4) {				// y < 2775
		
	}
	if (App->ui->curr_check <= 5) {				// y < 2000
		App->enemies->AddEnemy(ROOMBA, 197, 1091, &roomba1);
		App->enemies->AddEnemy(ROOMBA, 197, 1123, &roomba2);
		App->enemies->AddEnemy(ROOMBA, 115, 1029, &roomba3);
	}
	if (App->ui->curr_check <= 6) {				// y < 479
		App->enemies->AddEnemy(BOSS, 88, -5);
	}
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
	RestartEnemiesPaths();

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
		App->render->Blit(lava, 0, 7350, &lavaanim.GetCurrentFrame());
		App->render->Blit(lava, 256, 7400, &lavaanim.GetCurrentFrame());
		/*App->render->Blit(lava, 0, 2896, &lavaanim.GetCurrentFrame());
		App->render->Blit(lava, 0, 5156, &lavaanim.GetCurrentFrame());*/

		//App->render->Blit(sublighttex, 0, 6781, &sublightanim.GetCurrentFrame());
		App->render->Blit(graphics_l4_below, 0, 0, &level4);
		App->render->Blit(graphics_l4, 0, 0, &level4); // Map
		//App->render->Blit(on_bg, 0, 8445, &lights.GetCurrentFrame());
		//platform stuff
		platform1_aux_pos = platform1_pos + platform_p.GetCurrentSpeed();
		App->render->Blit(platform_t, platform1_aux_pos.x , platform1_aux_pos.y, &platform_anim.GetCurrentFrame());
		platform_1_1->SetPos(platform1_aux_pos.x - SCREEN_WIDTH-184, platform1_aux_pos.y);
		platform_1_2->SetPos(platform1_aux_pos.x + 84, platform1_aux_pos.y);
		if (platform1_aux_pos.x > SCREEN_WIDTH + 150){
			platform_p.Restart();
		}

		platform2_aux_pos = platform2_pos - platform_p.GetCurrentSpeed();
		App->render->Blit(platform_t, platform2_aux_pos.x, platform2_aux_pos.y, &platform_anim.GetCurrentFrame());
		platform_2_1->SetPos(platform2_aux_pos.x - SCREEN_WIDTH-106, platform2_aux_pos.y);
		platform_2_2->SetPos(platform2_aux_pos.x + 84, platform2_aux_pos.y);
		if (platform2_aux_pos.x < -150) platform_p.Restart();

		platform3_aux_pos = platform3_pos + platform_p.GetCurrentSpeed();
		App->render->Blit(platform_t, platform3_aux_pos.x, platform3_aux_pos.y, &platform_anim.GetCurrentFrame());
		platform_3_1->SetPos(platform3_aux_pos.x - SCREEN_WIDTH - 184, platform3_aux_pos.y);
		platform_3_2->SetPos(platform3_aux_pos.x + 84, platform3_aux_pos.y);
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
	gb21.Restart();
}