#include "texture.h"
#include <iostream>

void Texture::SetState(SDL_State& state_)
{
    state = &state_;
    if (state != nullptr)
    {
        std::cout << "[Texture::SetState] Texture state set successfully.\n";
    }
    else
    {
        std::cout << "[Texture::SetState] ERROR: Texture state set unsuccessfully!\n";
    }
}

void Texture::LoadTexture(std::string filepath)
{
    std::string texturePath = filepath;
    if (state == nullptr)
    {
        std::cout << "[Texture::LoadTexture] ERROR: Texture state not set!\n";
        return;
    }
    else
    {
        texture = IMG_LoadTexture(state->renderer, texturePath.c_str());
        if (!texture)
        {
            texture = IMG_LoadTexture(state->renderer, fallbackPath.c_str());
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "texture null reference", nullptr);
        }
        std::cout << "[Texture::LoadTexture] Texture set successfully\n";
    }
}

void Texture::Render()
{
    if (state == nullptr)
    {
        std::cout << "[Texture::Render] ERROR: Texture state is null!\n";
        return;
    }
    //std::cout << "[Texture::Render] Texture should be rendering. If not being seen, its because rect's not set.\n";
    SDL_RenderTexture(state->renderer, texture, &textureSrc, &transform);
}