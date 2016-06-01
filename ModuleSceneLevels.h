#ifndef __MODULESCENELEVELS_H__
#define __MODULESCENELEVELS_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "Path.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

class ModuleSceneLevels : public Module
{
public:
	ModuleSceneLevels();
	~ModuleSceneLevels();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool CameraReset();
	bool train_dead;
	bool train_first_time = true;
	bool first_path_made = false;
	bool train_start_path = false;
	void RestartEnemiesPaths();
	void RestartEnemies();
	void AddEnergyBox(int x, int y);
	void AddChangeBox(int x, int y);

	int now;
	int last_enemy;
	float purple_background_1 = 1055;
	float purple_background_2 = 1567;
	float purple_background_3 = 2079;
	float purple_background_4 = 2591;
	float purple_background_5 = 3103;

public:

	SDL_Texture* graphics_l4 = nullptr;
	SDL_Texture* graphics_l4_below = nullptr;
	SDL_Texture* lava = nullptr;
	SDL_Texture* on_bg = nullptr;
	SDL_Texture* sublighttex = nullptr;
	SDL_Texture* graphics_l4_below_purple = nullptr;

	Animation lavaanim;
	Animation sublightanim;
	Animation lights;

	SDL_Rect level4;
	SDL_Rect level4_purple_background;

	float camera_y;

	Mix_Music* level4_song;

	Path gb1;
	Path gb2;
	Path gb3;
	Path gb4;
	Path gb5;
	Path gb6;
	Path gb7;
	Path gb8;
	Path gb9;
	Path gb10;
	Path gb11;
	Path gb12;
	Path gb13;
	Path gb14;
	Path gb15;
	Path gb16;
	Path gb17;
	Path gb18;
	Path gb19;
	Path gb20;
	Path gb21;
	Path gb22;
	Path gb23;
	Path gb24;
	Path gb25;

	Path roomba1;
	Path roomba2;
	Path roomba3;
	Path notsobasic1;
	Path notsobasic2;
	Path notsobasic3;
	Path notsobasic4;
	Path notsobasic5;
	Path notsobasic6;
	Path notsobasic7;
	Path notsobasic8;
	Path notsobasic9;
	Path notsobasic10;
	Path notsobasic11;
	Path notsobasic12;
	Path notsobasic13;
	Path notsobasic14;
	Path notsobasic15;
	Path notsobasic16;
	Path notsobasic17;
	Path notsobasic18;
	Path notsobasic19;
	Path notsobasic20;
	Path notsobasic21;
	Path notsobasic22;
	Path notsobasic23;
	Path notsobasic24;
	Path turret;

	Path doyouevenyolo1;
	Path doyouevenyolo2;
	Path doyouevenyolo3;
	Path doyouevenyolo4;

	Path doyouevenyolo5;
	Path doyouevenyolo6;
	Path doyouevenyolo7;
	Path doyouevenyolo8;

	Path verticalyolo1;
	Path verticalyolo2;
	Path verticalyolo3;
	Path verticalyolo4;
	Path verticalyolo5;
	Path verticalyolo6;
	Path verticalyolo7;
	Path verticalyolo8;
	Path verticalyolo9;
	Path verticalyolo10;
	Path verticalyolo11;
	Path verticalyolo12;

	Path fastright;
	Path fastright1;
	Path fastright2;
	Path fastright3;
	Path sl1;
	Path sl2;
	Path sl3;
	Path sl4;
	Path sl5;
	Path sl6;

	Path mt1;
	Path mt2;
	Path mt3;
	Path mt4;
	Path mt5;
	Path mt6;
	Path mt7;
	Path mt8;
	Path mt9;
	Path mt10;
	Path mt11;
	Path mt12;
	Path mt13;
	Path mt14;
	Path mt15;
	Path mt16;
	Path mt17;
	Path mt18;
	Path mt19;
	Path mt20;
	Path mt21;
	Path mt22;
	Path mt23;

	//Platform stuff
	Path platform_p1;
	Path platform_p2;
	Path platform_p3;
	Animation platform_anim;
	SDL_Texture* platform_t = nullptr;
	iPoint platform1_pos;
	iPoint platform1_aux_pos;
	Collider* platform_1_1;
	Collider* platform_1_2;
	iPoint platform2_pos;
	iPoint platform2_aux_pos;
	Collider* platform_2_1;
	Collider* platform_2_2;
	iPoint platform3_pos;
	iPoint platform3_aux_pos;
	Collider* platform_3_1;
	Collider* platform_3_2;
	Collider* platformr1;
	Collider* platformr2;
	Collider* platforml;

	// train
	Path train_platform_first_path;
	Path train_platform_loop_path;
	Path train_platform_death_path;
	Path current_train_path;
	Animation train_platform_anim;
	SDL_Texture* train_platform_tex = nullptr;
	iPoint train_platform_pos;
	iPoint train_platform_pos_aux;
	Collider* train_platform_coll_left;
	Collider* train_platform_coll_right;
	Path notsobasic_train;
};

#endif // __MODULESCENELevels_H__