#include <iostream>
#include "timer.h"

void Timer::SetState(SDL_State& state_)
{
	state = &state_;
}

void Timer::Start()
{
	count = true;
	time = 0.0f;
}

void Timer::Stop()
{
	count = false;
	time = 0.0f;
}

void Timer::Update()
{
	if (count)
	{
		time += 1.0f * (float)state->delta;
		if (time >= waitTime)
		{
			// send a request to the caller that we are done counting.
			Stop();
		}
	}
}