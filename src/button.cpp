#include "button.h"

void Button::SetState(SDL_State& state_)
{
	state = &state_;
}

void Button::SetInput(Input& input_)
{
	input = &input_;
}

void Button::SetSize(Vector2 vec2)
{
	size = vec2;
}

void Button::SetPosition(Vector2 vec2)
{
	position = vec2;
}

void Button::Update()
{
	if (input->mousePositionX > position.x && input->mousePositionX < position.x + size.x && input->mousePositionY > position.y && input->mousePositionY < position.y + size.y)
	{
		if (input->IsMouseButtonPressed(SDL_BUTTON_LEFT))
		{
		}
		if (input->IsMouseButtonJustPressed(SDL_BUTTON_LEFT))
		{
			std::cout << "[Button::Update] Mouse button just pressed.\n";
		}
		if (input->IsMouseButtonJustReleased(SDL_BUTTON_LEFT))
		{
			std::cout << "[Button::Update] Mouse button just released.\n";
		}
		//std::cout << "[Button::Update] Mouse position: " << input->mousePositionX << ".X, " << input->mousePositionY << ".Y\n";
		//std::cout << "[Button::Update] Button position: " << position.x << ".X, " << position.y << ".Y\n";
	}
}
