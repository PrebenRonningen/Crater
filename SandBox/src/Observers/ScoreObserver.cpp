#include "CraterPCH.h"
#include "ScoreObserver.h"
#include "Components/ScoreComponent.h"

#include "Services/ServiceLocator.h"
#include "Services/Sound/SimpleSDL2AudioMaster.h"
#include "Services/Sound/LoggingSoundSystem.h"

void ScoreObserver::OnNotify(const CraterEngine::GameObject& pObject, const CraterEngine::EventType& event)
{
	ScoreComponent* pScoreComponent = pObject.GetComponent<ScoreComponent>();

	switch ( event )
	{
		case CraterEngine::EventType::ColorChange:
				pScoreComponent->AddToScore(25);
				ServiceLocator::GetSoundService().PlaySound("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door2.wav", 50);
			break;
		case CraterEngine::EventType::DefetedCoilyWithFlyingDisc:
				pScoreComponent->AddToScore(500);
				ServiceLocator::GetSoundService().Pause();
			break;
		case CraterEngine::EventType::DiscRemaining:
				pScoreComponent->AddToScore(50);
				ServiceLocator::GetSoundService().UnPause();
			break;
		case CraterEngine::EventType::CaughtSlick:
				pScoreComponent->AddToScore(300);
				ServiceLocator::GetSoundService().ToggleMuted();
			break;
		case CraterEngine::EventType::CaughtSam:
				pScoreComponent->AddToScore(300);
				ServiceLocator::GetSoundService().ToggleMuted();
			break;
		default:
			break;
	}
}
