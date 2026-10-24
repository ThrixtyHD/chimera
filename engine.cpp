#include "engine.h"

void Engine::SetState(SDL_State& state_)
{
	state = &state_;
}
void Engine::SetDebug(DebugConsole& console_)
{
	debugConsole = &console_;
	RegisterCommands();
}

void Engine::LoadTexture(SDL_Texture& texture, std::string path)
{

}

void Engine::RegisterCommands()
{
	debugConsole->RegisterCommand("window_display_mode_fullscreen", "Sets the window display mode to fullscreen", 0, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
	{
		SDL_SetWindowFullscreen(state->window, true);
		return {};
	});
	debugConsole->RegisterCommand("window_display_mode_windowed", "Sets the window display mode to windowed", 0, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
	{
		SDL_SetWindowFullscreen(state->window, false);
		return {};
	});
	debugConsole->RegisterCommand("window_display_mode_bordered", "Sets the window display mode to bordered", 0, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
	{
		SDL_SetWindowBordered(state->window, true);
		return {};
	});
	debugConsole->RegisterCommand("window_display_mode_borderless", "Sets the window display mode to borderless", 0, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
	{
		SDL_SetWindowBordered(state->window, false);
		return {};
	});

	debugConsole->RegisterCommand("window_display_mode_resizeable_enable", "window_display_mode_resizeable_enable", 0, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
	{
		SDL_SetWindowResizable(state->window, true);
		return {};
	});
	debugConsole->RegisterCommand("window_display_mode_resizeable_disable", "window_display_mode_resizeable_disable", 0, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
	{
			SDL_SetWindowResizable(state->window, false);
		return {};
	});
}


void Engine::Render()
{
	for (int i = 0; i < labels.size(); i++)
	{
		labels[i]->Render();
	}
}