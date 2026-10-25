#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "boot.h"
#include "c_math.h"

class ColorRect
{
public:
	SDL_State* state = nullptr;

	SDL_FRect transform;

	Vector2 position = { 0.0f, 0.0f };
	Vector2 size = { 0.0f, 0.0f };
	Color color = { 0.0f, 0.0f, 0.0f, 0.0f };

	bool Visible = true;

	void SetState(SDL_State& state_);
	void SetColor(Color rgba);
	void SetSize(Vector2 xy);
	void SetPosition(Vector2 xy);
	void Render();
};
