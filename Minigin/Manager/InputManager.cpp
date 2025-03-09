
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>


bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
		//process ImGui events
		ImGui_ImplSDL2_ProcessEvent(&e);
	}	

	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	// Get controller state
	XINPUT_STATE controllerState{};
	bool controllerConnected = (XInputGetState(0, &controllerState) == ERROR_SUCCESS); // Assume controller 0

    for (auto& inputMapping : m_InputMappings)
    {
        bool actionTriggered = false;
        // checks for keyboard
        for (auto& key : inputMapping->SDLkeys)
        {
            if (keyState[key])
            {
                inputMapping->SetKeyState(true);
                actionTriggered = true;
                break;
            }
        }
        // check controller
        if (controllerConnected)
        {
            for (auto& button : inputMapping->GamepadButtons)
            {
                if (controllerState.Gamepad.wButtons & button)
                {
                    inputMapping->SetKeyState(true);
                    actionTriggered = true;
                    break;
                }
            }
        }

        // Execute if the key state matches the action state
        if (inputMapping->CurrentKeyStateIsActionState())
        {
            inputMapping->command->execute();
        }

        // else reset it
        if (!actionTriggered)
        {
            inputMapping->SetKeyState(false);
        }
    }


	return true;
}
