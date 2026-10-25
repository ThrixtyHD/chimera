#pragma once
#include <string>
#include "texture.h"
#include "c_math.h"

class TextureRect : Texture
{
public:
	SDL_State* state = nullptr;

	Texture texture;

	Vector2 position = { 0.0f, 0.0f };
	Vector2 size = { 0.0f, 0.0f };
	float rotation = 0.0f;

	// default creatng the texture rect to being visible.
	bool Visible = true;

	enum TEXTURE_RECT_ORIGIN
	{
		TEXTURE_RECT_ORIGIN_TOP_LEFT,
		TEXTURE_RECT_ORIGIN_TOP_RIGHT,
		TEXTURE_RECT_ORIGIN_BOTTOM_LEFT,
		TEXTURE_RECT_ORIGIN_BOTTOM_RIGHT,
		TEXTURE_RECT_ORIGIN_TOP,
		TEXTURE_RECT_ORIGIN_BOTTOM,
		TEXTURE_RECT_ORIGIN_LEFT,
		TEXTURE_RECT_ORIGIN_RIGHT,
		TEXTURE_RECT_ORIGIN_CENTER,
	};

	TEXTURE_RECT_ORIGIN textureRectOrigin = TEXTURE_RECT_ORIGIN_TOP_LEFT;

	void UpdateTextureSrc();
	void UpdateTransform();

	void SetState(SDL_State& state_);
	void SetTexture(std::string filepath);
	void SetXY(Vector2 xy);
	void SetWH(Vector2 wh);
	void SetOrigin(TEXTURE_RECT_ORIGIN origin);
	void SetPosition(Vector2 xy);
	void SetRotation(float r);
	void SetRotationDegrees(float r);
	void SetSize(Vector2 xy);
	void SetGlobalPosition(Vector2 xy);
	void SetGlobalRotation(float r);
	void SetGlobalRotationDegrees(float r);
	void Show();
	void Hide();
	void Update();
	void Render();
};
