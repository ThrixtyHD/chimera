#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "boot.h"

class Texture
{
public:
	SDL_State* state = nullptr;

	Texture() 
	{
	};

	SDL_FRect textureSrc;
	SDL_FRect transform;

	float textureSrc_X = 0.0f;
	float textureSrc_Y = 0.0f;
	float textureSrc_W = 0.0f;
	float textureSrc_H = 0.0f;

	float transform_X = 0.0f;
	float transform_Y = 0.0f;
	float transform_W = 0.0f;
	float transform_H = 0.0f;

	std::string fallbackPath = "textures/missing_tex";

	SDL_Texture* texture = nullptr;
	void SetState(SDL_State& state_);
	void LoadTexture(std::string filepath);
	void Render();
};
