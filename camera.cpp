#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <iostream>
#include <string>

#include "camera.h"

void Camera::Create()
{
    // node func
}

float Camera::PositionCameraBased(float value)
{
    return value;
}

void Camera::Position(float x, float y)
{
    cameraPositionX = x;
    cameraPositionY = y;
    
    /*
    // clamp position x from falling out of bounds.
    if (cameraPositionX > 0)
    {
        cameraPositionX = 0;
    }

    // clamp position x from falling out of bounds.
    if (cameraPositionY > 0)
    {
        cameraPositionY = 0;
    }
    */
}

void Camera::PositionCenter(float x, float y)
{
    focusPositionX = -x - (-state->currentWindowWidth / (cameraZoom * 2.0f)) - 8.0f;
    focusPositionY = -y - (-state->currentWindowHeight / (cameraZoom * 2.0f)) - 8.0f;

    cameraPositionX = focusPositionX;
    cameraPositionY = focusPositionY;

    // clamp position x from falling out of bounds.
    if (cameraPositionX > 0)
    {
        cameraPositionX = 0;
    }

    // clamp position x from falling out of bounds.
    if (cameraPositionY > 0)
    {
        cameraPositionY = 0;
    }

    // clamp position x from falling out of bounds.
    if (cameraPositionY < -304)
    {
        //cameraPositionY = -304;
    }
}

void Camera::Zoom()
{
}

void Camera::GrabWindowSize()
{
    // sets the camera variables to the state's so i can use them.
    currentWindowWidth = state->currentWindowWidth;
    currentWindowHeight = state->currentWindowHeight;

    // focus pos's are what the center is.
    //focusPositionX = currentWindowWidth / 2;
    //focusPositionY = currentWindowHeight / 2;

}


void Camera::SetState(SDL_State& state_)
{
	state = &state_;
}

void Camera::SetConsole(DebugConsole& console_)
{
    console = &console_;
    RegisterCommands(console_);
}



void Camera::MoveCameraWithInputs(int direction, double deltaTime)
{
    if (direction == 0)
    {
        cameraPositionY -= moveSpeed * deltaTime;
    }
    if (direction == 1)
    {
        cameraPositionY += moveSpeed * deltaTime;
    }
    if (direction == 2)
    {
        cameraPositionX -= moveSpeed * deltaTime;
    }
    if (direction == 3)
    {
        cameraPositionX += moveSpeed * deltaTime;
    }
}


void Camera::RegisterCommands(DebugConsole& console)
{
    console.RegisterCommand("camera_pos", "Outputs a test warning", 2, [this, &console](const std::vector<std::string>& arguments) -> std::vector<std::string>
    {

        cameraPositionX = std::stof(arguments[1]);
        cameraPositionY = std::stof(arguments[2]);

        console.Output("Camera position X set to " + std::to_string(cameraPositionX) + " and Camera position Y set to " + std::to_string(cameraPositionY) + "");

        Position(cameraPositionX, cameraPositionY);
        return {};
    });

    console.RegisterCommand("camera_zoom", "Outputs a test warning", 1, [this](const std::vector<std::string>& arguments) -> std::vector<std::string>
        {
            cameraZoom = std::stof(arguments[1]);
            Zoom();
            return {};
        });
}