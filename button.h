#pragma once
#include "c_math.h"
#include "boot.h"
#include "input.h"
#include "sprite.h"

#include <iostream>
class Button
{
public:
	Button() = default;
	SDL_State* state = nullptr;
	Input* input = nullptr;
	Vector2 size = { 0, 0 };
	Vector2 position = { 0, 0 };

	void SetState(SDL_State& state_);
	void SetInput(Input& input_);
	void SetSize(Vector2 vec2);
	void SetPosition(Vector2 vec2);

	void Update();
};