#pragma once
#include <CraterEngine.h> 
#include "Components/MovementComponent.h"
class MoveDownLeftCommand final : public CraterEngine::Command
{
public:
	MoveDownLeftCommand(CraterEngine::GameObject* pObject)
	{
		m_pObject = pObject;
	};
	virtual ~MoveDownLeftCommand() override
	{
	};

#pragma region deleted
	MoveDownLeftCommand(const MoveDownLeftCommand& other) = delete;
	MoveDownLeftCommand(MoveDownLeftCommand&& other) = delete;
	MoveDownLeftCommand& operator=(const MoveDownLeftCommand& other) = delete;
	MoveDownLeftCommand& operator=(MoveDownLeftCommand&& other) = delete;
#pragma endregion

	virtual void Execute() override
	{


	};
private:
	CraterEngine::GameObject* m_pObject;
};