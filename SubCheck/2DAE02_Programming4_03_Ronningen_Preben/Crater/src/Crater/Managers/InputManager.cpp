#include "CraterPCH.h"
#include "InputManager.h"
#include "Crater/Controller/Xbox360Controller.h"
#include "Crater/Commands/Command.h"
#include <cassert>
#include <algorithm>
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
		m_Keys.clear();

		for ( auto& c : m_Controllers )
		{
			if ( c )
			{
				delete c;
				c = nullptr;
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
			ImGui_ImplSDL2_ProcessEvent(&e);
			if ( e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE )
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
				auto command = m_Keys.find(std::tuple(controllerId, ControllerButton(keysChecked), buttonState));
				if ( command != m_Keys.end() ) m_Keys[command->first]->Execute();
			}
			++keysChecked;
			key = key << 1;
		}
	}

	bool InputManager::AssignCommand(const std::tuple<unsigned int, ControllerButton, ButtonState>& commandKey, Command* command)
	{
		auto existingCommand = m_Keys.find(commandKey);
		if ( existingCommand == m_Keys.end())
		{
			m_Keys[commandKey] = command;
			return true;
		}
		else if ( typeid( *existingCommand->second ) != typeid( *command ) )
		{
			delete m_Keys[commandKey];
			m_Keys[commandKey] = command;
			return true;
		}

			try
			{
				if(typeid( *existingCommand->second ) == typeid( *command ) )
					throw std::runtime_error("Command already set: ");
			}
			catch ( const std::runtime_error& e )
			{
				std::string what = typeid( *command ).name();
				what = what.substr(what.find_last_of(':')+1, what.size() - what.find_last_of(':'));
				std::cout << e.what() << what << " already set to key [User(" << std::get<0>(commandKey) << "), Button(" << (int)std::get<1>(commandKey) << "), State(" << (int)std::get<2>(commandKey) <<")]" << std::endl;
			}

		delete command;
		return false;
	}
}