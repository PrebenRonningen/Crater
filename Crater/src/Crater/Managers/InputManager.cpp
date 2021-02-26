#include "CraterPCH.h"
#include "InputManager.h"
#include "Crater/Controller/Xbox360Controller.h"
#include "Crater/Commands/Command.h"
#include <SDL.h>

namespace CraterEngine
{
	InputManager::InputManager()
	{
		for ( int i{}; i < XUSER_MAX_COUNT; ++i )
		{
			m_Controllers[i] = new Xbox360Controller;
		}
	}

	void InputManager::Destroy()
	{
		for ( auto& com : m_Keys )
		{
			if ( com.second )
			{
				delete com.second;
				com.second = nullptr;
			}
		}
	}

	bool InputManager::UpdateControllers()
	{
		for ( auto& c : m_Controllers )
		{
			ZeroMemory(&c->ZeroState(), sizeof(XINPUT_STATE));
		}

		bool handleInput = false;
		for ( DWORD i{}; i < XUSER_MAX_COUNT; ++i )
		{
			if ( XInputGetState(i, &m_Controllers[i]->UpdateState()) == ERROR_SUCCESS )
			{
				m_Controllers[i]->SetID(i);
				m_Controllers[i]->UpdateKeys();
				handleInput = true;
			}
			else
			{
				m_Controllers[i]->SetID(-1);
			}
		}
		return handleInput;
	}

	bool InputManager::ProcessInput()
	{
		//Controller Input handling
		if(UpdateControllers())
			HandleControllerInput();

		//Window, Keyboard & Mouse Events handling
		SDL_Event e;
		while ( SDL_PollEvent(&e) )
		{
			if ( e.type == SDL_QUIT )
			{
				return false;
			}
			if ( e.type == SDL_KEYDOWN )
			{

			}
			if ( e.type == SDL_MOUSEBUTTONDOWN )
			{

			}
		}
		return true;
	}

	void InputManager::HandleControllerInput()
	{
		for ( DWORD i{}; i < XUSER_MAX_COUNT; ++i )
		{
			if ( m_Controllers[i]->GetID() == -1 ) continue;
			
			for ( ButtonState state : m_Controllers[i]->GetKeyInfo().actions )
			{
				if(state == ButtonState::NONE ) continue;
				OnAction(m_Controllers[i]->GetID(), m_Controllers[i]->GetKeyInfoFromState(state), state);
			}
		}
	}

	void InputManager::OnAction(const int controllerId, const uint16_t keyInfo, const ButtonState buttonState)
	{
		uint32_t key = 1;
		uint8_t keysChecked{ 0 };
		while ( key <= keyInfo )
		{
			if ( key & keyInfo )
			{
				auto command = m_Keys[std::tuple(controllerId, ControllerButton(keysChecked), buttonState)];
				if ( command != nullptr ) command->Execute();
			}
			++keysChecked;
			key = key << 1;
		}
	}

	bool InputManager::AssignCommand(const std::tuple<unsigned int, ControllerButton, ButtonState>& commandKey, Command* command)
	{
		if ( m_Keys[commandKey] == nullptr )
		{
			m_Keys[commandKey] = command;
			return true;
		}
		return false;
	}
}