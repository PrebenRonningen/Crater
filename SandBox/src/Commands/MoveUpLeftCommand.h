#pragma once
#include <CraterEngine.h> 
#include "Components/MovementComponent.h"
class MoveUpLeftCommand final : public CraterEngine::Command
{
public:
	MoveUpLeftCommand(CraterEngine::GameObject* pObject)
	{
		m_pObject = pObject;
	};
	virtual ~MoveUpLeftCommand() override
	{
	};

#pragma region deleted
	MoveUpLeftCommand(const MoveUpLeftCommand& other) = delete;
	MoveUpLeftCommand(MoveUpLeftCommand&& other) = delete;
	MoveUpLeftCommand& operator=(const MoveUpLeftCommand& other) = delete;
	MoveUpLeftCommand& operator=(MoveUpLeftCommand&& other) = delete;
#pragma endregion

	virtual void Execute() override
	{


	};
private:
	CraterEngine::GameObject* m_pObject;
};