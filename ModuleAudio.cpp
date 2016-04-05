#include "ModuleAudio.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "SDL_mixer\include\SDL_mixer.h"

ModuleAudio::ModuleAudio(){

	level1 = nullptr;
	level2 = nullptr;
	level3 = nullptr;
    last_song = nullptr;
}

ModuleAudio::~ModuleAudio(){}

bool ModuleAudio::Init(){

	LOG("Init Audio Module........");

	if (Mix_Init(MIX_INIT_OGG) < 0) {
		LOG("AudioModule can't initialize: %s/n", Mix_GetError());
	}
	else {
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) LOG("AudioModule can't open: %s", Mix_GetError());
	}

	level1 = Mix_LoadMUS("Sounds/Music/level1.ogg");
	if (level1 == NULL) LOG("Level1 Audio loading fail: %s.", Mix_GetError());
	level2 = Mix_LoadMUS("Sounds/Music/level2.ogg");
	if (level2 == NULL) LOG("Level2 Audio loading fail: %s.", Mix_GetError());
	level3 = Mix_LoadMUS("Sounds/Music/level3.ogg");
	if (level3 == NULL) LOG("Level3 Audio loading fail: %s.", Mix_GetError());
	continue_song = Mix_LoadMUS("Sounds/Music/continue.ogg");
	if (level3 == NULL) LOG("Continue Audio loading fail: %s.", Mix_GetError());
	gameover = Mix_LoadMUS("Sounds/Music/gameover.ogg");
	if (level3 == NULL) LOG("GameOver Audio loading fail: %s.", Mix_GetError());
	laser_shoot = Mix_LoadMUS("Sounds/Effects/basic_laser_shoot.wav");
	if (level3 == NULL) LOG("GameOver Audio loading fail: %s.", Mix_GetError());

	return true;
}

bool ModuleAudio::CleanUp(){
	
	LOG("Cleaning Audio -------------");

	Mix_HaltMusic();

	if (level1 != NULL){
		Mix_FreeMusic(level1);
	}
	if (level2 != NULL){
		Mix_FreeMusic(level2);
	}
	if (level3 != NULL){
		Mix_FreeMusic(level3);
	}
	if (continue_song != NULL){
		Mix_FreeMusic(continue_song);
	}
	if (gameover != NULL){
		Mix_FreeMusic(gameover);
	}
	if (laser_shoot != NULL){
		Mix_FreeMusic(laser_shoot);
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

void ModuleAudio::StopAudio(){

	Mix_HaltMusic();
}

void ModuleAudio::ResetState(){

	last_song = NULL;
}

void ModuleAudio::PlayMusic(Mix_Music* to_play, Repetitions n_times){

	if (to_play != last_song){
		Mix_PlayMusic(to_play, n_times);
		last_song = to_play;
	}
}

bool ModuleAudio::IsPlaying(){
	if (Mix_PlayingMusic() == 1) return true;
	else return false;
}