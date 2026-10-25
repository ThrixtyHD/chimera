#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <iostream>
#include <string>

#include "boot.h"
#ifdef _DEBUG
	#include "debug_console.h"
#endif

class Camera
{
public:
	SDL_State* state;
	DebugConsole* console;
	float cameraPositionX = 0.0f;
	float cameraPositionY = 0.0f;
	float cameraZoom = 4.0f;
	float moveSpeed = 256.0f;

	// From the state. half it to get the center.
	int currentWindowWidth = 0;
	int currentWindowHeight = 0;

	float focusPositionX = 0.0f;
	float focusPositionY = 0.0f;

	void Create();
	void Position(float x, float y);
	void PositionCenter(float x, float y);
	void GrabWindowSize();

	float PositionCameraBased(float value);

	void Zoom();
	void MoveCameraWithInputs(int direction, double deltaTime);
	void SetState(SDL_State& state);
#ifdef _DEBUG
	void SetConsole(DebugConsole& console_);
	void RegisterCommands(DebugConsole& console);
#endif

};
