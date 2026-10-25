#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SDL3/SDL.h>

struct Action
{
	std::string actionName = "";
	SDL_Scancode actionKey = SDL_SCANCODE_UNKNOWN;
};

class Input
{
public:
	// keyboard key
	bool currentFrameKeyboardKeyInput[SDL_SCANCODE_COUNT] = {};
	bool previousFrameKeyboardKeyInput[SDL_SCANCODE_COUNT] = {};

	static constexpr int MOUSE_BUTTON_COUNT = 6;

	// mouse button
	bool currentFrameMouseButtonInput[MOUSE_BUTTON_COUNT] = {};
	bool previousFrameMouseButtonInput[MOUSE_BUTTON_COUNT] = {};


	std::string currentTargetActionName = "";

	const bool* keys = SDL_GetKeyboardState(nullptr);

	std::vector<Action> actions{};

	float mousePositionX = 0.0f;
	float mousePositionY = 0.0f;

	void Create();
	void CreateAction(std::string action, SDL_Scancode scancode);

	void ResetInputChecks();

	bool OnKeyDown(SDL_Scancode scancode);
	bool OnKeyUp(SDL_Scancode scancode);

	bool IsKeyPressed(SDL_Scancode scancode);
	bool IsKeyJustPressed(SDL_Scancode scancode);
	bool IsKeyJustReleased(SDL_Scancode scancode);

	bool IsActionPressed(std::string action);
	bool IsActionJustPressed(std::string action);
	bool IsActionJustReleased(std::string action);

	bool IsMouseButtonPressed(Uint8 button);
	bool IsMouseButtonJustPressed(Uint8 button);
	bool IsMouseButtonJustReleased(Uint8 button);

};
