#pragma once
#include <CraterEngine.h> 
#include "Components/MovementComponent.h"
class MoveUpRightCommand final : public CraterEngine::Command
{
public:
	MoveUpRightCommand(CraterEngine::GameObject* pObject)
		: m_pObject(pObject)
	{
		m_pMovementComponent = m_pObject->GetComponent<MovementComponent>();
	};
	virtual ~MoveUpRightCommand() override
	{
	};

#pragma region deleted
	MoveUpRightCommand(const MoveUpRightCommand& other) = delete;
	MoveUpRightCommand(MoveUpRightCommand&& other) = delete;
	MoveUpRightCommand& operator=(const MoveUpRightCommand& other) = delete;
	MoveUpRightCommand& operator=(MoveUpRightCommand&& other) = delete;
#pragma endregion

	virtual void Execute() override
	{
		m_pMovementComponent->MoveUpRight();
	};
private:
	CraterEngine::GameObject* m_pObject;
	MovementComponent* m_pMovementComponent;
};