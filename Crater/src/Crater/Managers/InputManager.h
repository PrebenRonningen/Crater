#pragma once
#include <XInput.h>
#include "Crater/Singleton.h"
#include <map>
#include <tuple>

namespace CraterEngine
{
	class Command;
	enum class ButtonState
	{
		NONE = 0,
		ButtonDown = 1,
		ButtonUp = 2,
		ButtonRepeat = 4
	};

	enum class ControllerButton
	{
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRigh,

		Start,
		Back,
		LThumbPress,
		RThumbPress,

		LShoulder,
		RShoulder,

		LTrigger,
		RTrigger,

		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class Xbox360Controller;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Destroy();
		bool ProcessInput();
		bool AssignCommand(const std::tuple<unsigned int, ControllerButton, ButtonState>& commandKey, Command* command);
	private:
		friend class Singleton<InputManager>;
		InputManager();
		
		/*returns TRUE if a controller was updated.
		returns FALSE if no controllers are connected.*/
		bool UpdateControllers();
		void HandleControllerInput();
		void OnAction(const int controllerId, const uint16_t keyInfo, const ButtonState buttonState);
		std::map<std::tuple<unsigned int, ControllerButton, ButtonState>, Command*> m_Keys{};
		Xbox360Controller* m_Controllers[XUSER_MAX_COUNT];

		static const std::uint8_t AmountOfButtons = 16;
	};
}