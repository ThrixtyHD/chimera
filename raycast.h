#pragma once
#include "boot.h"
#include "c_math.h"

class RayCast
{
public:
	RayCast() = default;
	SDL_State* state = nullptr;
	Vector2 position = { 0.0f, 0.0f };
	Vector2 target_position = { 0.0f, 0.0f };

	void SetState(SDL_State& state_);
	void SetPosition(Vector2 xy);
	void SetTargetPosition(Vector2 xy);
	void Update();
};