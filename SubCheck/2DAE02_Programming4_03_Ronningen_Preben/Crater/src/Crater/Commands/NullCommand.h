#pragma once

#include "Crater/Commands/Command.h"
namespace CraterEngine
{
	class NullCommand : public Command
	{
	public:
		NullCommand(){};
		virtual ~NullCommand() override{};

		#pragma region deleted
		NullCommand(const NullCommand& other) = delete;
		NullCommand(NullCommand&& other) = delete;
		NullCommand& operator=(const NullCommand& other) = delete;
		NullCommand& operator=(NullCommand&& other) = delete;
		#pragma endregion
		
		virtual void Execute() override{};
	private:

	};
}