#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "boot.h"
#include "debug_console.h"
#include "input.h";

class Game
{
public:
	virtual ~Game() = default;
	virtual bool Create(SDL_State& state_, DebugConsole& debugConsole_, Input& input_) = 0;
	virtual void Update(double delta) {};
	virtual void Render() {};
	virtual void Event(const SDL_State& state, SDL_Event& event, Input& input_) {};
	virtual void Destroy() {};
};

class Chimera
{
	public:
	int Run(Game& game);
	void Update();
	void DrawLayers();
	void CleanUp();
};
