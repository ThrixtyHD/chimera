#include <iostream>
#include "raycast.h"

void RayCast::SetState(SDL_State& state_)
{
	state = &state_;
}

void RayCast::SetPosition(Vector2 position_)
{
	position.x = position_.x;
	position.y = position_.y;
}

void RayCast::SetTargetPosition(Vector2 target_position_)
{
	target_position.x = target_position_.x;
	target_position.y = target_position_.y;
}

void RayCast::Update()
{
}
