#pragma once
#include "Components/HealthComponent.h"

class LoseLifeCommand final : public CraterEngine::Command
{
public:
	LoseLifeCommand(CraterEngine::GameObject* pObject)
	{
		m_pObject = pObject;
	};
	virtual ~LoseLifeCommand() override
	{
	};

#pragma region deleted
	LoseLifeCommand(const LoseLifeCommand& other) = delete;
	LoseLifeCommand(LoseLifeCommand&& other) = delete;
	LoseLifeCommand& operator=(const LoseLifeCommand& other) = delete;
	LoseLifeCommand& operator=(LoseLifeCommand&& other) = delete;
#pragma endregion

	virtual void Execute() override
	{
		HealthComponent* pHealthComp = m_pObject->GetComponent<HealthComponent>();
		if ( pHealthComp != nullptr )
		{
			pHealthComp->LoseHealth(1);
		}
	};
private:
	CraterEngine::GameObject* m_pObject;
};