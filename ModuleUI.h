#ifndef _ModuleUI_
#define _ModuleUI_

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "dynArray.h"
#include "ModuleTextures.h"
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
	void UpdateCreditnum();
	void UpdateScorenums();
	void UpdateTopScorenums();
	void UpdateLivesnums();
	SDL_Rect* GetCorrectNum(const int& num);
	void DrawPlayerScore();
	void DrawPlayerScore(int x, int y);
	void DrawTopScore();
	void DrawBombs();
	void AddCoin();
	void AddBomb();
	void AddEnergy();
	void SubCoin();
	void SubBomb();
	void RestetEnergyBombs();
	bool TopScore();

public:

	dynArray<CheckPoint> checkpoints;
	int curr_check = 0;

	dynArray<Ranking> TopScores;
	char* rank1;
	char* rank2;
	char* rank3;
	char* rank4;
	char* rank5;

	int lives=0;
	int score=0;
	int energy=0;
	int max_energy = 36;
	int bombs=0;
	int credit=0;

	int top_score;

	int now;
	int e_timer;

	bool game = false;
	bool title = true;
	bool cont = false;
	bool dead = false;

	SDL_Texture* ui_graphics;

	Animation player1;
	Animation player2;
	SDL_Rect player1_static;
	SDL_Rect player2_title;

	SDL_Rect num0;
	SDL_Rect num1;
	SDL_Rect num2;
	SDL_Rect num3;
	SDL_Rect num4;
	SDL_Rect num5;
	SDL_Rect num6;
	SDL_Rect num7;
	SDL_Rect num8;
	SDL_Rect num9;

	SDL_Rect lives0;
	SDL_Rect lives1;
	SDL_Rect lives2;
	SDL_Rect lives_symbol;

	SDL_Rect energy_bar;
	SDL_Rect energy_bar_ext;
	SDL_Rect energy_pill;

	SDL_Rect gameover;

	SDL_Rect top;

	SDL_Rect bomb;

	SDL_Rect* score1=nullptr;
	SDL_Rect* score10 = nullptr;
	SDL_Rect* score100 = nullptr;
	SDL_Rect* score1000 = nullptr;
	SDL_Rect* score10000 = nullptr;
	SDL_Rect* score100000 = nullptr;
	SDL_Rect* score1000000 = nullptr;
	SDL_Rect* lives_num = nullptr;
	SDL_Rect* p2_score = nullptr;

	SDL_Rect* topscore1 = nullptr;
	SDL_Rect* topscore10 = nullptr;
	SDL_Rect* topscore100 = nullptr;
	SDL_Rect* topscore1000 = nullptr;
	SDL_Rect* topscore10000 = nullptr;
	SDL_Rect* topscore100000 = nullptr;
	SDL_Rect* topscore1000000 = nullptr;

	SDL_Rect credits;
	SDL_Rect c0;
	SDL_Rect c1;
	SDL_Rect c2;
	SDL_Rect c3;
	SDL_Rect c4;
	SDL_Rect c5;
	SDL_Rect c6;
	SDL_Rect c7;
	SDL_Rect c8;
	SDL_Rect c9;

	SDL_Rect* c_num = nullptr;

};

#endif