#ifndef _ModuleAudio_
#define _ModuleAudio_

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"


class ModuleAudio : public Module{
public:

	ModuleAudio();

	// Destructor
	~ModuleAudio();

	
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();

	// Called before quitting
	bool CleanUp();

public:
	
	Mix_Music* level1;
	Mix_Music* level2;
	Mix_Music* level3;
	Mix_Music* to_play;
	Mix_Music* last_song;


};

#endif
