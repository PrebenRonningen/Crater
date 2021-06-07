#include "SandBoxPCH.h"
#include "ScoreObserver.h"
#include "Components/ScoreComponent.h"

#include "Services/ServiceLocator.h"
#include "Services/Sound/SimpleSDL2AudioMaster.h"
#include "Services/Sound/LoggingSoundSystem.h"

void ScoreObserver::OnNotify(const CraterEngine::GameObject* pObject)
{
	if( !pObject->HasComponent<ScoreComponent>() ) return;

	ScoreComponent* pScoreComponent = pObject->GetComponent<ScoreComponent>();
	if( !pScoreComponent->HasEvent() ) return;

	switch ( pScoreComponent->GetEvent() )
	{
		case ScoreComponent::ScoreEvent::ColorChange:
			pScoreComponent->AddToScore(25);
			//ServiceLocator::GetSoundService().PlaySound("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door2.wav", 50);
			break;
		//case ScoreComponent::ScoreEvent::DefetedCoilyWithFlyingDisc:
		//	pScoreComponent->AddToScore(500);
		//	ServiceLocator::GetSoundService().Pause();
		//	break;
		//case ScoreComponent::ScoreEvent::DiscRemaining:
		//	pScoreComponent->AddToScore(50);
		//	ServiceLocator::GetSoundService().UnPause();
		//	break;
		//case ScoreComponent::ScoreEvent::CaughtSlick:
		//	pScoreComponent->AddToScore(300);
		//	ServiceLocator::GetSoundService().ToggleMuted();
		//	break;
		//case ScoreComponent::ScoreEvent::CaughtSam:
		//	pScoreComponent->AddToScore(300);
		//	ServiceLocator::GetSoundService().ToggleMuted();
		//	break;
		default:
			break;
	}
	pScoreComponent->EventHandeled();
}
