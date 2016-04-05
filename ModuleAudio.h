#ifndef _ModuleAudio_
#define _ModuleAudio_

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_SONGS 20
#define MAX_EFFECTS 50

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
	void PlaySoundEffect(Mix_Chunk* to_play);
	bool IsPlaying();

	// Utility methods
	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadSoundEffect(const char* path);
	bool UnloadMusic(Mix_Music* music);
	bool UnloadSoundEffect(Mix_Chunk* effect);

public:
	
	Mix_Music* songs[MAX_SONGS];
	uint last_song = 0;

	Mix_Chunk* sound_effects[MAX_EFFECTS];
	uint last_effect = 0;

	Mix_Music* prev_song;

};

#endif
