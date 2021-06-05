#pragma once
#include "CraterEngine.h"
#include "Components/ScoreComponent.h"
class ScoreCommand final : public CraterEngine::Command
{
public:
	ScoreCommand(CraterEngine::GameObject* pObject, ScoreComponent::ScoreEvent scoreEvent)
	{
		m_pObject = pObject;
		m_Event = scoreEvent;
	};
	virtual ~ScoreCommand() override
	{
	};

	#pragma region deleted
	ScoreCommand(const ScoreCommand& other) = delete;
	ScoreCommand(ScoreCommand&& other) = delete;
	ScoreCommand& operator=(const ScoreCommand& other) = delete;
	ScoreCommand& operator=(ScoreCommand&& other) = delete;
	#pragma endregion

	virtual void Execute() override
	{
		m_pObject->GetComponent<ScoreComponent>()->SetEvent(m_Event);
		m_pObject->Notify();
	};
private:
	CraterEngine::GameObject* m_pObject;
	ScoreComponent::ScoreEvent m_Event;
};