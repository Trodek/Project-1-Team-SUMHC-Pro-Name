#ifndef _ModuleAudio_
#define _ModuleAudio_

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"

enum Repetitions {
	LOOP = -1, ONCE, TWICE, THRICE

};

class ModuleAudio : public Module{
public:

	ModuleAudio();

	// Destructor
	~ModuleAudio();

	
	bool Init();

	// Called before quitting
	bool CleanUp();

	// Audio methods
	void StopAudio();
	void ResetState();
	void PlayMusic(Mix_Music* to_play, Repetitions n_times);
	bool IsPlaying();

public:
	
	Mix_Music* level1;
	Mix_Music* level2;
	Mix_Music* level3;
	Mix_Music* continue_song;
	Mix_Music* gameover;
	Mix_Music* last_song;
	Mix_Music* laser_shoot;


};

#endif
