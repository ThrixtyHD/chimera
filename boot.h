#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

class Label;

class SDL_State
{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width = 1280;
    int height = 720;
    int logWidth = width;
    int logHeight = height;

    // the total amount of frames passed in the application.
    Uint32 frames = 0;


    int currentWindowWidth = width;
    int currentWindowHeight = height;

    bool running = true;

    enum WindowState
    {
        WINDOW_STATE_WINDOWED,
        WINDOW_STATE_FULLSCREEN,
        WINDOW_STATE_BORDERLESS_WINDOWED
    };

    WindowState windowState = WINDOW_STATE_WINDOWED;

    // for now, but move this into a engine class next time.
    std::vector<Label*> labels{};

    void CleanUpSDL3();
    bool InitialiseState();


    void Texture();

    void RenderLabels();
};
