#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>

#include "label.h"
#include "boot.h"
#include "debug_console.h"
#include "camera.h"
#include "engine.h"
#include "button.h"


#include "chimera.h"


int Chimera::Run(Game& game)
{
    SDL_State state;
    if (!state.InitialiseState())
    {
        return 1;
    }

    DebugConsole console;
    console.SetState(state);
    console.Initialise(state);

    Engine engine;
    engine.SetState(state);
    engine.SetDebug(console);

    Input input;
    input.Create();
    if (!game.Create(state, console, input))
    {
        return 0;
    }
    // "debug_key" is used to open and close console aswell as executing other debug key shortcut functions 
    input.CreateAction("debug_key", SDL_SCANCODE_GRAVE);
    input.CreateAction("test", SDL_SCANCODE_P);

    Uint64 now;
    Uint64 before = SDL_GetPerformanceCounter();;
    double delta = 0;

    // const bool* keys = SDL_GetKeyboardState(nullptr);
    while (state.running)
    {
        input.ResetInputChecks();
        state.frames++;
        if (state.frames >= 4294967295)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Total elapsed frames of the program will exceed over 4294967295. Aborting...", nullptr);
            state.running = false;
        }

        SDL_GetWindowSize(state.window, &state.currentWindowWidth, &state.currentWindowHeight);
        now = SDL_GetPerformanceCounter();
        delta = (now - before) / (double)SDL_GetPerformanceFrequency();

        // give state the delta.
        state.delta = delta;
        before = now;

        SDL_Event event{ 0 };
        SDL_StartTextInput(state.window);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                case SDL_EVENT_MOUSE_BUTTON_UP:
                {
                    if (event.button.button < input.MOUSE_BUTTON_COUNT)
                    {
                        input.currentFrameMouseButtonInput[event.button.button] = event.button.down;
                    }
                }
                case SDL_EVENT_MOUSE_MOTION: 
                {
                    input.mousePositionX = event.motion.x;
                    input.mousePositionY = event.motion.y;
                    break;
                }
                case SDL_EVENT_QUIT:
                {
                    state.running = false;
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    state.width = event.window.data1;
                    state.height = event.window.data2;
                    break;
                }
                case SDL_EVENT_TEXT_INPUT:
                {
                    console.GrabInputEvents(event);
                    break;
                }
                case SDL_EVENT_KEY_UP:
                {
                    // when the current scancode is detected, change its state. this starts the prev and current comparison checks.
                    input.OnKeyUp(event.key.scancode);
                    break;
                }
                case SDL_EVENT_KEY_DOWN:
                {
                    // when the current scancode is detected, change its state. this starts the prev and current comparison checks.
                    input.OnKeyDown(event.key.scancode); 
                    if (input.IsKeyPressed(SDL_SCANCODE_BACKSPACE))
                    {
                        console.RemoveCharFromString();
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_UP))
                    {
                        console.ScrollHistory(1);
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_DOWN))
                    {
                        console.ScrollHistory(0);
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_LEFT))
                    {
                        console.MovePosition(0);
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_RIGHT))
                    {
                        console.MovePosition(1);
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_RETURN))
                    {
                        console.ProcessCommand(state);
                    }
                    if (input.IsKeyJustPressed(SDL_SCANCODE_TAB))
                    {
                        console.AutoComplete();
                    }
                    if (input.IsKeyJustPressed(SDL_SCANCODE_TAB))
                    {
                        console.AutoComplete();
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_PAGEUP))
                    {
                        console.ScrollOutput(0);
                    }
                    if (input.IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
                    {
                        console.ScrollOutput(1);
                    }
                    break;
                }
            }
        }

        

        if (input.IsActionJustReleased("debug_key"))
        {
            console.ToggleConsole();
        }

        if (input.IsMouseButtonJustPressed(SDL_BUTTON_LEFT))
        {
            //console.ToggleConsole();
        }

        game.Update(delta);
        
        SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);               // draw clear buffer
        SDL_RenderClear(state.renderer);

        // the engine render's all game elements here.
        game.Render();
        console.Update(state, delta);
        SDL_RenderPresent(state.renderer);
    }

    // game elements get cleaned up here.
    game.Destroy();
    //
    state.CleanUpSDL3();
    return 0;
}
