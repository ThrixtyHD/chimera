#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>
#include "boot.h"
#include "debug_console.h"
#include <memory>
#include "label.h"


class Engine
{
private:
	std::vector<std::unique_ptr<Label>> labels;
public:
	SDL_State* state = nullptr;
	DebugConsole* debugConsole = nullptr;

	//Label& CreateLabel();
	void SetState(SDL_State& state_);
	void SetDebug(DebugConsole& console_);
	void RegisterCommands();
	void LoadTexture(SDL_Texture& texture, std::string path);
	void Render();
};
