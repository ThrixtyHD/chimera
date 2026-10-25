#include "texture_rect.h"

void TextureRect::SetState(SDL_State& state_)
{
    state = &state_;
    texture.SetState(*state);
}

void TextureRect::SetTexture(std::string filepath)
{
    std::string texturePath = "textures/player/player.png";
    // make sure to set the state.
    texture.LoadTexture(filepath);

    // Here, we would set the textureSrc but idk how to automatically r... wait. i import a image and i automatically read its dimensions and set it,
}

void TextureRect::SetPosition(Vector2 xy)
{
    position = xy;

    UpdateTextureSrc();
    UpdateTransform();
}

void TextureRect::SetRotation(float r)
{

}

void TextureRect::SetOrigin(TEXTURE_RECT_ORIGIN origin)
{
    switch (origin)
    {
    case TEXTURE_RECT_ORIGIN_TOP_LEFT:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_TOP_LEFT;
        break;
    case TEXTURE_RECT_ORIGIN_TOP_RIGHT:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_TOP_RIGHT;
        break;
    case TEXTURE_RECT_ORIGIN_BOTTOM_LEFT:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_BOTTOM_LEFT;
        break;
    case TEXTURE_RECT_ORIGIN_BOTTOM_RIGHT:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_BOTTOM_RIGHT;
        break;
    case TEXTURE_RECT_ORIGIN_TOP:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_TOP;
        break;
    case TEXTURE_RECT_ORIGIN_BOTTOM:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_BOTTOM;
        break;
    case TEXTURE_RECT_ORIGIN_LEFT:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_LEFT;
        break;
    case TEXTURE_RECT_ORIGIN_RIGHT:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_RIGHT;
        break;
    case TEXTURE_RECT_ORIGIN_CENTER:
        textureRectOrigin = TEXTURE_RECT_ORIGIN_CENTER;
        break;
    }
}

void TextureRect::UpdateTextureSrc()
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

void TextureRect::UpdateTransform()
{
    // idk if this idea will work but i hope it does.

    switch (textureRectOrigin)
    {
    case TEXTURE_RECT_ORIGIN_TOP_LEFT:
        // default is 0, 0 top left.
        texture.transform =
        {
            texture.transform_X,
            texture.transform_Y,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case TEXTURE_RECT_ORIGIN_TOP_RIGHT:
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
    case TEXTURE_RECT_ORIGIN_BOTTOM_LEFT:
        texture.transform =
        {
            texture.transform_X,
            texture.transform_Y - texture.textureSrc_H,
            texture.transform_W,
            texture.transform_H
        };
    case TEXTURE_RECT_ORIGIN_BOTTOM_RIGHT:
        texture.transform =
        {
            texture.transform_X - texture.textureSrc_W,
            texture.transform_Y - texture.textureSrc_H,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case TEXTURE_RECT_ORIGIN_TOP:
        texture.transform =
        {
            texture.transform_X - (texture.textureSrc_W / 2.0f),
            texture.transform_Y,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case TEXTURE_RECT_ORIGIN_BOTTOM:
        texture.transform =
        {
            texture.transform_X - (texture.textureSrc_W / 2.0f),
            texture.transform_Y - texture.textureSrc_H,
            texture.transform_W,
            texture.transform_H
        };
        break;
    case TEXTURE_RECT_ORIGIN_LEFT:
        texture.transform =
        {
            texture.transform_X,
            texture.transform_Y - (texture.textureSrc_H / 2.0f),
            texture.transform_W,
            texture.transform_H
        };
        break;
    case TEXTURE_RECT_ORIGIN_RIGHT:
        texture.transform =
        {
            texture.transform_X - texture.textureSrc_W,
            texture.transform_Y - (texture.textureSrc_H / 2.0f),
            texture.transform_W,
            texture.transform_H
        };
        break;
    case TEXTURE_RECT_ORIGIN_CENTER:
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

void TextureRect::SetRotationDegrees(float r)
{
    //SDL_RenderTextureRotated(state->renderer, texture.texture, )
}

void TextureRect::SetXY(Vector2 xy)
{
    texture.textureSrc_X = xy.x;
    texture.textureSrc_Y = xy.y;

    UpdateTextureSrc();
    UpdateTransform();
}

void TextureRect::SetWH(Vector2 wh)
{
    texture.textureSrc_W = wh.x;
    texture.textureSrc_H = wh.y;

    UpdateTextureSrc();
    UpdateTransform();
}

void TextureRect::SetSize(Vector2 wh)
{
    texture.transform_W = wh.x;
    texture.transform_H = wh.y;

    UpdateTextureSrc();
    UpdateTransform();
}

void TextureRect::SetGlobalPosition(Vector2 xy)
{

}

void TextureRect::SetGlobalRotation(float r)
{

}

void TextureRect::SetGlobalRotationDegrees(float r)
{

}

void TextureRect::Update()
{
    texture.transform_X = position.x;
    texture.transform_Y = position.y;

    UpdateTextureSrc();
    UpdateTransform();
}

void TextureRect::Show()
{
    Visible = true;
}

void TextureRect::Hide()
{
    Visible = false;
}

void TextureRect::Render()
{
    if (Visible)
    {
        texture.Render();
    }
}
