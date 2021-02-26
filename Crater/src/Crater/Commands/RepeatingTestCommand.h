#pragma once
#include "Crater/Commands/Command.h"
#include <iostream>
namespace CraterEngine
{
	class RepeatingTestCommand : public Command
	{
	public:
		RepeatingTestCommand()
		{
		};
		virtual ~RepeatingTestCommand() override
		{
		};

#pragma region deleted
		RepeatingTestCommand(const RepeatingTestCommand& other) = delete;
		RepeatingTestCommand(RepeatingTestCommand&& other) = delete;
		RepeatingTestCommand& operator=(const RepeatingTestCommand& other) = delete;
		RepeatingTestCommand& operator=(RepeatingTestCommand&& other) = delete;
#pragma endregion

		virtual void Execute() override
		{
			std::cout << "Repeating!" << std::endl;
		};
	private:

	};
}