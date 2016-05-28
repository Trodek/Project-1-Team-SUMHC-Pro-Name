#include "ModuleAudio.h"
#include "Application.h"
#include "ModuleSceneLevels.h"
#include "SDL_mixer\include\SDL_mixer.h"

ModuleAudio::ModuleAudio(){

    prev_song = nullptr;
}

ModuleAudio::~ModuleAudio(){}

bool ModuleAudio::Init(){

	LOG("Init Audio Module........");

	if (Mix_Init(MIX_INIT_OGG) < 0) {
		LOG("AudioModule can't initialize: %s/n", Mix_GetError());
		return false;
	}
	else {
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0){
			LOG("AudioModule can't open: %s", Mix_GetError());
			return false;
		}
	}


	return true;
}

bool ModuleAudio::CleanUp(){
	
	LOG("Cleaning Audio -------------");

	Mix_HaltMusic();

	for (uint i = 0; i < MAX_SONGS; i++){
		if (songs[i] != nullptr){
			Mix_FreeMusic(songs[i]);
		}
	}
	for (uint i = 0; i < MAX_EFFECTS; i++){
		if (sound_effects[i] != nullptr){
			Mix_FreeChunk(sound_effects[i]);
		}
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

void ModuleAudio::StopAudio(){

	Mix_HaltMusic();
	ResetState();
}

void ModuleAudio::ResetState(){

	prev_song = nullptr;
}

void ModuleAudio::PlayMusic(Mix_Music* to_play, Repetitions n_times){

	if (to_play != prev_song){
		Mix_PlayMusic(to_play, n_times);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
		prev_song = to_play;
	}
}

void ModuleAudio::PlaySoundEffect(Mix_Chunk* to_play){

	Mix_PlayChannel(-1, to_play, 0);
}

bool ModuleAudio::IsPlaying(){

	if (Mix_PlayingMusic() == 1) return true;
	else return false;
}

Mix_Music* const ModuleAudio::LoadMusic(const char* path){

	Mix_Music* music = nullptr;
	music = Mix_LoadMUS(path);

	if (music == nullptr){
		LOG("Could not load song with path: %s. Error: %s.", path, Mix_GetError());
	}
	else{
		songs[last_song++] = music;
	}

	return music;
}

Mix_Chunk* const ModuleAudio::LoadSoundEffect(const char* path){

	Mix_Chunk* effect = nullptr;
	effect = Mix_LoadWAV(path);

	if (effect == nullptr){
		LOG("Could not load sound effect with path: %s. Error: %s.", path, Mix_GetError());
	}
	else{
		sound_effects[last_effect++] = effect;
	}

	return effect;
}

bool ModuleAudio::UnloadMusic(Mix_Music* music){

	for (uint i = 0; i < MAX_SONGS; i++){
		if (songs[i] == music){
			Mix_FreeMusic(songs[i]);
			songs[i] = nullptr;
			break;
		}
	}
	return true;
}

bool ModuleAudio::UnloadSoundEffect(Mix_Chunk* effect){

	for (uint i = 0; i < MAX_SONGS; i++){
		if (sound_effects[i] == effect){
			Mix_FreeChunk(sound_effects[i]);
			sound_effects[i] = nullptr;
			break;
		}
	}
	return true;
}