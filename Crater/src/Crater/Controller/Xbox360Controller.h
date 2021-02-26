#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include <bitset>
#include <array>
#include <utility> 

namespace CraterEngine
{
	class Command;
	class Xbox360Controller
	{
		struct KeyInfo
		{
			std::uint16_t keyPressed;
			std::uint16_t keyReleased;
			std::uint16_t keyRepeating;
			std::array<ButtonState,3> actions{};
		} m_KeyInfo;

	public:
		Xbox360Controller() = default;
		~Xbox360Controller() = default;
		#pragma region deleted
		Xbox360Controller(const Xbox360Controller& other) = delete;
		Xbox360Controller(Xbox360Controller&& other) = delete;
		Xbox360Controller& operator=(const Xbox360Controller& other) = delete;
		Xbox360Controller& operator=(Xbox360Controller&& other) = delete;
		#pragma endregion

		XINPUT_STATE& UpdateState()
		{
			return m_CurrentControllerStates;
		};
		XINPUT_STATE& ZeroState()
		{
			m_PreviousControllerStates = m_CurrentControllerStates;
			return m_CurrentControllerStates;
		};

		void UpdateKeys()
		{
			m_KeyInfo.keyPressed = std::uint16_t((m_CurrentControllerStates.Gamepad.wButtons ^ m_PreviousControllerStates.Gamepad.wButtons ) & m_CurrentControllerStates.Gamepad.wButtons);
			m_KeyInfo.keyReleased = std::uint16_t(( m_CurrentControllerStates.Gamepad.wButtons ^ m_PreviousControllerStates.Gamepad.wButtons ) & m_PreviousControllerStates.Gamepad.wButtons);
			m_KeyInfo.keyRepeating = std::uint16_t(( m_CurrentControllerStates.Gamepad.wButtons & m_PreviousControllerStates.Gamepad.wButtons ));
			//explenation
			{
			//What is going on here
			//Calculate what button newly got pressed
			//	0011 0101 previous state
			//	0101 0110 current state  
			//	xor ^		//XOR current and precious state with eachother to remove any unpressed keys or repeating keys
			//r	0110 0011
			//	0101 0110 curent state
			//	and &		//AND the result with current state to get the newly pressed keys
			//r	0100 0010	

			// do the same but and with previous state to get what keys got released

			// AND current and previous states to get what keys are repeating
			} 
			m_KeyInfo.actions = { 
				m_KeyInfo.keyPressed ? ButtonState::ButtonDown : ButtonState::NONE,
				m_KeyInfo.keyReleased ? ButtonState::ButtonUp : ButtonState::NONE,
				m_KeyInfo.keyRepeating ? ButtonState::ButtonRepeat : ButtonState::NONE
			};
		};

		inline const KeyInfo& GetKeyInfo() const { return m_KeyInfo; };
		inline const std::uint16_t GetKeyInfoFromState(const ButtonState& keyState) const
		{
			switch ( keyState )
			{
				case ButtonState::ButtonDown:
					return m_KeyInfo.keyPressed;
					break;
				case ButtonState::ButtonUp:
					return m_KeyInfo.keyReleased;
					break;
				case ButtonState::ButtonRepeat:
					return m_KeyInfo.keyRepeating;
					break;
			}
			return 0;
		};
		inline int GetID() const {	return m_ID; };
		inline void SetID(const int id) { m_ID = id; };
	private:
		XINPUT_STATE m_CurrentControllerStates{};
		XINPUT_STATE m_PreviousControllerStates{};
		int m_ID = -1;
	};
}

