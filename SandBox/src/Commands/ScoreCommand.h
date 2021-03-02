#pragma once
#include "CraterEngine.h"

class ScoreCommand : public CraterEngine::Command
{
public:
	ScoreCommand(CraterEngine::GameObject* pObject, const CraterEngine::EventType& eventType)
	{
		m_pObject = pObject;
		m_Event = eventType;
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
		m_pObject->Notify(*m_pObject, m_Event);
	};
private:
	CraterEngine::GameObject* m_pObject;
	CraterEngine::EventType m_Event;
};