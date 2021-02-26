#pragma once
#include "Crater/Commands/Command.h"
#include <iostream>
namespace CraterEngine
{
	class PressedTestCommand : public Command
	{
	public:
		PressedTestCommand()
		{
		};
		virtual ~PressedTestCommand() override
		{
		};

#pragma region deleted
		PressedTestCommand(const PressedTestCommand& other) = delete;
		PressedTestCommand(PressedTestCommand&& other) = delete;
		PressedTestCommand& operator=(const PressedTestCommand& other) = delete;
		PressedTestCommand& operator=(PressedTestCommand&& other) = delete;
#pragma endregion

		virtual void Execute() override
		{
			std::cout << "Pressed!" << std::endl;
		};
	private:

	};
}