#pragma once
#include <CraterEngine.h> 
#include "Components/MovementComponent.h"
class MoveDownRightCommand final : public CraterEngine::Command
{
public:
	MoveDownRightCommand(CraterEngine::GameObject* pObject)
		: m_pObject(pObject)
	{
		m_pMovementComponent = m_pObject->GetComponent<MovementComponent>();
	};
	virtual ~MoveDownRightCommand() override
	{
	};

#pragma region deleted
	MoveDownRightCommand(const MoveDownRightCommand& other) = delete;
	MoveDownRightCommand(MoveDownRightCommand&& other) = delete;
	MoveDownRightCommand& operator=(const MoveDownRightCommand& other) = delete;
	MoveDownRightCommand& operator=(MoveDownRightCommand&& other) = delete;
#pragma endregion

	virtual void Execute() override
	{
		m_pMovementComponent->MoveDownRight();
	};
private:
	CraterEngine::GameObject* m_pObject;
	MovementComponent* m_pMovementComponent;
};