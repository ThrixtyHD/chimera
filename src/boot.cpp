#include "boot.h"
#include "label.h"

void SDL_State::CleanUpSDL3()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SDL_State::InitialiseState()
{
    bool initSuccess = true;

    //InitialiseSDL();
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialise SDL3.", nullptr);
        initSuccess = false;
    }
    //CreateSDLWindow(state);
    // create SDL3 window
    
    switch (windowState)
    {
    case SDL_State::WINDOW_STATE_WINDOWED:
        break;
    case SDL_State::WINDOW_STATE_FULLSCREEN:
        break;
    case SDL_State::WINDOW_STATE_BORDERLESS_WINDOWED:
        break;
    default:
        break;
    }
    window = SDL_CreateWindow("scissor", width, height, SDL_WINDOW_RESIZABLE); // SDL_WINDOW_RESIZABLE - 0
    if (!window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to create window.", window);
        CleanUpSDL3();
        initSuccess = false;
    }
    //CreateSDLRenderer(state);
    // create renderer
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to create renderer.", window);
        CleanUpSDL3();
        initSuccess = false;
    }
    // configure presentation

    SDL_SetRenderLogicalPresentation(renderer, logWidth, logHeight, SDL_LOGICAL_PRESENTATION_DISABLED);
    return initSuccess;
}

void SDL_State::RenderLabels()
{
    for (int i = 0; i < labels.size(); i++)
    {
        labels[i]->Render();
    }
}

void SDL_State::Texture()
{
}
