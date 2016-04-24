#ifndef __PATH_H__
#define __PATH_H__

#include "p2Point.h"
#define MAX_STEPS 25

struct Step
{
	uint frames = 1;
	fPoint speed;
	Animation* animation = nullptr;
};

class Path
{
public:
	bool loop = true;
	Step steps[MAX_STEPS];
	fPoint accumulated_speed = {0.0f, 0.0f};

private:
	uint current_frame = 0;
	uint last_step = 0;
	fPoint prev_speed;
	bool moving;

public:

	void PushBack(fPoint speed, uint frames, Animation* animation = nullptr)
	{
		steps[last_step].animation = animation;
		steps[last_step].frames = frames;
		steps[last_step++].speed = speed;
	}

	iPoint GetCurrentSpeed(Animation** current_animation = nullptr)
	{
		current_frame += 1;

		prev_speed = accumulated_speed;

		uint count = 0;
		uint i = 0;
		bool need_loop = true;
		for(; i < last_step; ++i)
		{
			count += steps[i].frames;
			if(current_animation != nullptr)
				*current_animation = steps[i].animation;
			if(count >= current_frame)
			{
				accumulated_speed += steps[i].speed;
				if (accumulated_speed != prev_speed){
					moving = true;
					prev_speed = accumulated_speed;
				}
				else moving = false;
				need_loop = false;
				break;
			}
		}

		if(need_loop && loop)
			current_frame = 0;

		return iPoint((int)accumulated_speed.x, (int)accumulated_speed.y);
	}

	void Reset()
	{
		current_frame = 0;
	}

	bool Moving() const{
		return moving;
	}
};

#endif // __PATH_H__