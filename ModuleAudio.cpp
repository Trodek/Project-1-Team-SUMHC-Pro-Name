#include "ModuleAudio.h"
#include "Application.h"
#include "ModuleBackground.h"
#include "SDL_mixer\include\SDL_mixer.h"

ModuleAudio::ModuleAudio(){

	level1 = nullptr;
	level2 = nullptr;
	level3 = nullptr;
	to_play = nullptr;
        last_song = nullptr;
}

ModuleAudio::~ModuleAudio(){}

bool ModuleAudio::Init(){

	LOG("Initializing Audio Module........");

	if (Mix_Init(MIX_INIT_OGG) < 0) {
		LOG("AudioModule can't initialize: %s/n", Mix_GetError());
	}
	else { 
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) LOG("AudioModule can't open: %s", Mix_GetError()); 
	}

	return true;
}

bool ModuleAudio::Start(){

	level1 = Mix_LoadMUS("Sounds/Music/level1.ogg");
	if (level1 == NULL) LOG("Level1 Audio loading fail: %s.", Mix_GetError());
	level2 = Mix_LoadMUS("Sounds/Music/level2.ogg");
	if (level2 == NULL) LOG("Level2 Audio loading fail: %s.", Mix_GetError());
	level3 = Mix_LoadMUS("Sounds/Music/level3.ogg");
	if (level3 == NULL) LOG("Level3 Audio loading fail: %s.", Mix_GetError());

	return true;
}

update_status ModuleAudio::PreUpdate(){

	//hardcoded pixel where every level start
	if (App->background->map.y > 11489) to_play = level1;
	else if (App->background->map.y < 11489 && App->background->map.y > 6436) to_play = level2;
	else to_play = level3;

	return UPDATE_CONTINUE;
}

update_status ModuleAudio::Update(){

	if (to_play != last_song){
            Mix_HaltMusic();
            Mix_PlayMusic(to_play, -1);
            last_song = to_play;
        }

	return UPDATE_CONTINUE;
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

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}
