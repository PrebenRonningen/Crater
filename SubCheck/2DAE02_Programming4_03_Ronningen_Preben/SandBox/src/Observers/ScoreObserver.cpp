#include "CraterPCH.h"
#include "ScoreObserver.h"
#include "Components/ScoreComponent.h"

void ScoreObserver::OnNotify(const CraterEngine::GameObject& pObject, const CraterEngine::EventType& event)
{
	ScoreComponent* pScoreComponent = pObject.GetComponent<ScoreComponent>();

	switch ( event )
	{
		case CraterEngine::EventType::ColorChange:
				pScoreComponent->AddToScore(25);
			break;
		case CraterEngine::EventType::DefetedCoilyWithFlyingDisc:
				pScoreComponent->AddToScore(500);
			break;
		case CraterEngine::EventType::DiscRemaining:
				pScoreComponent->AddToScore(50);
			break;
		case CraterEngine::EventType::CaughtSlick:
				pScoreComponent->AddToScore(300);
			break;
		case CraterEngine::EventType::CaughtSam:
				pScoreComponent->AddToScore(300);
			break;
		default:
			break;
	}
}
