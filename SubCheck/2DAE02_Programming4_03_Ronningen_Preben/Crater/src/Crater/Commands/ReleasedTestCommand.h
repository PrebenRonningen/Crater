#pragma once
#include "Crater/Commands/Command.h"
#include <iostream>
namespace CraterEngine
{
	class ReleasedTestCommand : public Command
	{
	public:
		ReleasedTestCommand()
		{
		};
		virtual ~ReleasedTestCommand() override
		{
		};

#pragma region deleted
		ReleasedTestCommand(const ReleasedTestCommand& other) = delete;
		ReleasedTestCommand(ReleasedTestCommand&& other) = delete;
		ReleasedTestCommand& operator=(const ReleasedTestCommand& other) = delete;
		ReleasedTestCommand& operator=(ReleasedTestCommand&& other) = delete;
#pragma endregion

		virtual void Execute() override
		{
			std::cout << "Released!" << std::endl;
		};
	private:

	};
}