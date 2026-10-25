#pragma once
#include "boot.h"

// i guess the gist of a timer is a signal. so a vector of functions stored. 


// we need the state cuz it stores our delta
class Timer
{
public:
	Timer() = default;
	SDL_State* state = nullptr;
	float time = 0.0f;
	float waitTime = 1.0f;
	bool count = false;
	void SetState(SDL_State& state_);
	void Start();
	void Stop();
	void Update();
};