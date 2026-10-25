#include "sprite.h"

void Sprite::SetState(SDL_State& state_)
{
    state = &state_;
    texture.SetState(*state);
}

void Sprite::SetCameraBased()
{
    cameraBased = true;
}

void Sprite::SetCamera(Camera& camera_)
{
    camera = &camera_;
    if (camera != nullptr)
    {
        std::cout << "[Sprite::SetCamera] camera not null.\n";
    }
    //texture.SetCamera(*camera);
}

void Sprite::SetTexture(std::string filepath)
{
    std::string texturePath = "textures/player/player.png";
    // make sure to set the state.
    texture.LoadTexture(filepath);

    // Here, we would set the textureSrc but idk how to automatically r... wait. i import a image and i automatically read its dimensions and set it,
}

void Sprite::SetPosition(float x, float y)
{
    positionX = x;
    positionY = y;

    UpdateTextureSrc();
    UpdateTransform();
}

void Sprite::SetRotation(float r)
{

}

void Sprite::SetOrigin(SPRITE_ORIGIN origin)
{
    switch (origin)
    {
    case SPRITE_ORIGIN_TOP_LEFT:
        spriteOrigin = SPRITE_ORIGIN_TOP_LEFT;
        break;
    case SPRITE_ORIGIN_TOP_RIGHT:
        spriteOrigin = SPRITE_ORIGIN_TOP_RIGHT;
        break;
    case SPRITE_ORIGIN_BOTTOM_LEFT:
        spriteOrigin = SPRITE_ORIGIN_BOTTOM_LEFT;
        break;
    case SPRITE_ORIGIN_BOTTOM_RIGHT:
        spriteOrigin = SPRITE_ORIGIN_BOTTOM_RIGHT;
        break;
    case SPRITE_ORIGIN_TOP:
        spriteOrigin = SPRITE_ORIGIN_TOP;
        break;
    case SPRITE_ORIGIN_BOTTOM:
        spriteOrigin = SPRITE_ORIGIN_BOTTOM;
        break;
    case SPRITE_ORIGIN_LEFT:
        spriteOrigin = SPRITE_ORIGIN_LEFT;
        break;
    case SPRITE_ORIGIN_RIGHT:
        spriteOrigin = SPRITE_ORIGIN_RIGHT;
        break;
    case SPRITE_ORIGIN_CENTER:
        spriteOrigin = SPRITE_ORIGIN_CENTER;
        break;
    }
}

void Sprite::UpdateTextureSrc()
{
    // reupdate the frect.
    texture.textureSrc =
    {
        texture.textureSrc_X,
        texture.textureSrc_Y,
        texture.textureSrc_W,
        texture.textureSrc_H,
    };
}

void Sprite::UpdateTransform()
{
    // idk if this idea will work but i hope it does.

    switch (spriteOrigin)
    {
    case SPRITE_ORIGIN_TOP_LEFT:
        // default is 0, 0 top left.
        texture.transform =
        {
            texture.transform_X,
            texture.transform_Y,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_TOP_RIGHT:
        // if 0, 0 is the top right, y would be default and x would be the x size.
        texture.transform =
        {
            // modifying transform stays the same as we only add onto/remove onto.
            texture.transform_X - texture.textureSrc_W,
            texture.transform_Y,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_BOTTOM_LEFT:
        texture.transform =
        {
            texture.transform_X,
            texture.transform_Y - texture.textureSrc_H,
            texture.transform_W,
            texture.transform_H
        };
    case SPRITE_ORIGIN_BOTTOM_RIGHT:
        texture.transform =
        {
            texture.transform_X - texture.textureSrc_W,
            texture.transform_Y - texture.textureSrc_H,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_TOP:
        texture.transform =
        {
            texture.transform_X - (texture.textureSrc_W / 2.0f),
            texture.transform_Y,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_BOTTOM:
        texture.transform =
        {
            texture.transform_X - (texture.textureSrc_W / 2.0f),
            texture.transform_Y - texture.textureSrc_H,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_LEFT:
        texture.transform =
        {
            texture.transform_X,
            texture.transform_Y - (texture.textureSrc_H / 2.0f),
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_RIGHT:
        texture.transform =
        {
            texture.transform_X - texture.textureSrc_W,
            texture.transform_Y - (texture.textureSrc_H / 2.0f),
            texture.transform_W,
            texture.transform_H
        };
        break;
    case SPRITE_ORIGIN_CENTER:
        texture.transform =
        {
            texture.transform_X - (texture.textureSrc_W / 2.0f),
            texture.transform_Y - (texture.textureSrc_H / 2.0f),
            texture.transform_W,
            texture.transform_H
        };
        break;
    }

    
}

void Sprite::SetRotationDegrees(float r)
{
    //SDL_RenderTextureRotated(state->renderer, texture.texture, )
}

void Sprite::SetXY(float x, float y)
{
    texture.textureSrc_X = x;
    texture.textureSrc_Y = y;

    UpdateTextureSrc();
    UpdateTransform();
}

void Sprite::SetWH(float w, float h)
{
    texture.textureSrc_W = w;
    texture.textureSrc_H = h;

    UpdateTextureSrc();
    UpdateTransform();
}

void Sprite::SetSize(float w, float h)
{
    texture.transform_W = w;
    texture.transform_H = h;

    UpdateTextureSrc();
    UpdateTransform();
}

void Sprite::SetGlobalPosition(float x, float y)
{

}

void Sprite::SetGlobalRotation(float r)
{

}

void Sprite::SetGlobalRotationDegrees(float r)
{

}

void Sprite::Update()
{
    if (cameraBased) 
    {
        if (camera != nullptr)
        {
            texture.transform_X = positionX - camera->cameraPositionX;
            texture.transform_Y = positionY - camera->cameraPositionY;
            
        }
        else
        {
            texture.transform_X = positionX;
            texture.transform_Y = positionY;
        }
    }
    else
    {
        texture.transform_X = positionX;
        texture.transform_Y = positionY;
    }
    UpdateTextureSrc();
    UpdateTransform();
}

void Sprite::Show()
{
    Visible = true;
}

void Sprite::Hide()
{
    Visible = false;
}

void Sprite::Render()
{
    if (Visible)
    {
        texture.Render();
    }
}
