#ifndef _ModuleUI_
#define _ModuleUI_

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "dynArray.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Animation.h"
#include "dynArray.h"

class CheckPoint{
public:
	int camera_y=0;
	int x=105;
	int y = ((-camera_y) / 3) + 245;

public:
	CheckPoint(){}
	CheckPoint(const int camera) : camera_y(camera), x(105), y(((-camera_y) / 3) + 245){}
	CheckPoint(const CheckPoint& other) : camera_y(other.camera_y), x(other.x), y(other.y){}

};

struct Ranking {
	char* name;
	int area, Tscore;
};

class ModuleUI :public Module{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

	void SetGameStartConditions();

	void DrawBombs();

	void AddCoin();
	void SubCoin();

	void AddBomb();
	void SubBomb(char player);
	void ResetEnergyBombs();

	void AddEnergy();

	void GetScore();
	void Endlevel();

	void DrawNumber(int number, int x, int y, int variable, SDL_Rect Points);
	void DrawPlayer2Score(int number, int x, int y, int variable, SDL_Rect Points);
	bool TopScore();

public:

	dynArray<CheckPoint> checkpoints;
	int curr_check = 0;

	dynArray<Ranking> TopScores;

	int lives=0;
	int lives_p2 = 0;
	int score=0;
	int score_p2 = 0;
	int energy=0;
	int energy_p2 = 0;
	int max_energy = 36;
	int bombs=0;
	int bombs_p2 = 0;
	int credit=0;

	int top_score;

	int now;
	int e_timer;

	bool game = false;
	bool title = true;
	bool cont = false;
	bool dead = false;
	bool player2_dead = false;
	bool startgame = false;

	int temp_score;
	bool get_score;
	bool first_time;
	int temp_bomb;

	bool player2_enabled = false;


	SDL_Texture* low_energy;
	Animation Low_energy;
	Animation Low_energy_p2;

	SDL_Rect Low_energy_static;

	SDL_Texture* ui_graphics;

	Animation player1;
	SDL_Rect player1_static;

	Animation player2;
	SDL_Rect player2_title;

	Animation player2_name;
	SDL_Rect player2_static;

	SDL_Rect lives_symbol;
	SDL_Rect lives_num;

	SDL_Rect top_name;
	SDL_Rect top_points;

	Animation InsertCoin;
	SDL_Rect credits_name;
	SDL_Rect credits_num;

	SDL_Rect insert_coin;

	SDL_Rect energy_bar;
	SDL_Rect energy_bar_ext;
	SDL_Rect energy_pill;

	SDL_Rect energy_bar_p2;

	SDL_Rect gameover;

	SDL_Rect bomb;

	SDL_Rect stageclear;
	SDL_Rect bombpoints;
	SDL_Rect pink_numbers;
	SDL_Rect bomb_cont;

	uint e_dead;

	Mix_Chunk* coin_sound;
};

#endif