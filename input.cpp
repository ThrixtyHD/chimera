#include "input.h"

// if (!old_keys[key] && keys[key]) { /* pressed since last frame */ }
// if (old_keys[key] && !keys[key]) { /* released since last frame */ }
// if (old_keys[key] && keys[key]) { /* held since last frame */ }

void Input::Create()
{
	keys = SDL_GetKeyboardState(nullptr);
}

void Input::ResetInputChecks()
{
	// copy prev to current. 
	std::memcpy(previousFrameInput, currentFrameInput, sizeof(previousFrameInput));
}

bool Input::OnKeyDown(SDL_Scancode scancode) 
{ 
	currentFrameInput[scancode] = true; 
	return false;

}

bool Input::OnKeyUp(SDL_Scancode scancode) 
{ 
	currentFrameInput[scancode] = false; 
	return false;
}

bool Input::IsKeyPressed(SDL_Scancode scancode)
{
	bool isKeyPressed = false;
	if (currentFrameInput[scancode])
	{
		std::cout << "[Input::IsKeyPressed] Key: '" << scancode << "'.\n";
		isKeyPressed = true;
	}
	return isKeyPressed;
}

bool Input::IsKeyJustPressed(SDL_Scancode scancode)
{
	bool isKeyJustPressed = false;
	if (currentFrameInput[scancode] && !previousFrameInput[scancode])
	{
		std::cout << "[Input::IsKeyJustPressed] Key: '" << scancode << "'.\n";
		isKeyJustPressed = true;
	}
	return isKeyJustPressed;
}

bool Input::IsKeyJustReleased(SDL_Scancode scancode)
{
	bool isKeyJustReleased = false;
	if (!currentFrameInput[scancode] && previousFrameInput[scancode])
	{
		// std::cout << "[Input::IsKeyJustReleased] Key: '" << scancode << "'.\n";
		isKeyJustReleased = true;
	}
	return isKeyJustReleased;
}

void Input::CreateAction(std::string action, SDL_Scancode scancode)
{
	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i].actionName == action && actions[i].actionKey == scancode)
		{
			std::cout << "[Input::CreateAction] Error: Failed to create action: '" << action << "' because an action named: '" << action << "' with the key: '" << scancode << "' is already inside of the actions vector.\n";
			return;
		}
		else if (actions[i].actionName == action && actions[i].actionKey != scancode)
		{
			std::cout << "[Input::CreateAction] Error: Failed to create action: '" << action << "' because an action named: '" << action << "' is already inside of the actions vector however the key: '" << scancode << "' does not match. Did you enter the key wrong. Also, No. I have not programmed more than 1 for an action :).\n";
			return;
		}
	}
	std::cout << "[Input::CreateAction] Successfully created action: '" << action << "'.\n";
	Action newAction;
	newAction.actionName = action;
	newAction.actionKey = scancode;
	actions.push_back(newAction);
}

bool Input::IsActionPressed(std::string action)
{
	bool validAction = false;
	// maybe some shit like if currentFrameInput[scancode] is the same as the action's scancode, its valid?

	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i].actionName == action && currentFrameInput[actions[i].actionKey])
		{
			std::cout << "[Input::IsActionPressed] actionName: '" << actions[i].actionName << "' is the same as action: '" << action << "' which is found inside of the actions vector.\n";
			validAction = true;
		}
	}

	if (validAction)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::IsActionJustPressed(std::string action)
{
	bool validAction = false;
	// maybe some shit like if currentFrameInput[scancode] is the same as the action's scancode, its valid?

	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i].actionName == action) 
		{
			if (currentFrameInput[actions[i].actionKey] && !previousFrameInput[actions[i].actionKey])
			{
				std::cout << "[Input::IsActionJustPressed] actionName: '" << actions[i].actionName << "' is the same as action: '" << action << "' which is found inside of the actions vector.\n";
				validAction = true;
			}
		}
	}

	if (validAction)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::IsActionJustReleased(std::string action)
{
	bool validAction = false;
	// maybe some shit like if currentFrameInput[scancode] is the same as the action's scancode, its valid?

	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i].actionName == action)
		{
			if (!currentFrameInput[actions[i].actionKey] && previousFrameInput[actions[i].actionKey])
			{
				std::cout << "[Input::IsActionJustPressed] actionName: '" << actions[i].actionName << "' is the same as action: '" << action << "' which is found inside of the actions vector.\n";
				validAction = true;
			}
		}
	}

	if (validAction)
	{
		return true;
	}
	else
	{
		return false;
	}
}
