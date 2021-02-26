#pragma once

#include <cstdint>

namespace CraterEngine
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		#pragma region deleted
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
		#pragma endregion

		virtual void Execute() = 0;
	
	protected:
	};
}