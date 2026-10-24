#pragma once
#include "texture.h"
#include "camera.h"
#include <string>

class Sprite : Texture
{
public:
	SDL_State* state = nullptr;
	Camera* camera = nullptr;

	bool cameraBased = false;
	Texture texture;

	float positionX = 100.0f;
	float positionY = 0.0f;
	float rotation = 0.0f;

	// default creatng the sprite to being visible.
	bool Visible = true;

	enum SPRITE_ORIGIN
	{
		SPRITE_ORIGIN_TOP_LEFT,
		SPRITE_ORIGIN_TOP_RIGHT,
		SPRITE_ORIGIN_BOTTOM_LEFT,
		SPRITE_ORIGIN_BOTTOM_RIGHT,
		SPRITE_ORIGIN_TOP,
		SPRITE_ORIGIN_BOTTOM,
		SPRITE_ORIGIN_LEFT,
		SPRITE_ORIGIN_RIGHT,
		SPRITE_ORIGIN_CENTER,
	};

	SPRITE_ORIGIN spriteOrigin = SPRITE_ORIGIN_TOP_LEFT;

	void UpdateTextureSrc();
	void UpdateTransform();

	void SetState(SDL_State& state_);
	void SetCamera(Camera& camera_);
	void SetTexture(std::string filepath);
	void SetCameraBased();
	void SetXY(float x, float y);
	void SetWH(float w, float h);
	void SetOrigin(SPRITE_ORIGIN origin);
	void SetPosition(float x, float y);
	void SetRotation(float r);
	void SetRotationDegrees(float r);
	void SetSize(float x, float y);
	void SetGlobalPosition(float x, float y);
	void SetGlobalRotation(float r);
	void SetGlobalRotationDegrees(float r);
	void Show();
	void Hide();
	void Update();
	void Render();
};