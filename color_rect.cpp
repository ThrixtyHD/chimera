#include "color_rect.h"
#include <iostream>

void ColorRect::SetState(SDL_State& state_)
{
    state = &state_;
    if (state != nullptr)
    {
        std::cout << "[ColorRect::SetState] Texture state set successfully.\n";
    }
    else
    {
        std::cout << "[ColorRect::SetState] ERROR: Color rect state set unsuccessfully!\n";
    }
}

void ColorRect::SetSize(Vector2 vec2)
{
    size.x = vec2.x;
    size.y = vec2.y;

    transform.w = size.x;
    transform.h = size.y;
}

void ColorRect::SetPosition(Vector2 vec2)
{
    position.x = vec2.x;
    position.y = vec2.y;

    transform.x = position.x;
    transform.y = position.y;
}

void ColorRect::SetColor(Color color_)
{
    // change the colorRBGA to the new set color and apply it to the rendered rect.
    color = color_;

    std::cout << "[ColorRect::SetColor] Set color rect color to: '" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "'.\n";
}

void ColorRect::Render()
{
    if (state == nullptr)
    {
        std::cout << "[ColorRect::Render] ERROR: state is null!\n";
        return;
    }

    // i should move this out in the future. no point to keep setting it when it should already be set.
    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(state->renderer, &transform);

    if (!SDL_RenderFillRect(state->renderer, &transform))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to render ColorRect.", nullptr);
    }
}