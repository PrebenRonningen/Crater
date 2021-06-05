#include "SandBoxPCH.h"
#include "CraterEngine.h"
#include "HealthObserver.h"
#include "Components/HealthComponent.h"
#include "Components/PlayerComponent.h"
#include <iostream>
#include "Services/ServiceLocator.h"
#include "Services/Sound/SimpleSDL2AudioMaster.h"
#include "Services/Sound/LoggingSoundSystem.h"


void HealthObserver::OnNotify(const CraterEngine::GameObject* pObject)
{
	HealthComponent* pHealthComp = pObject->GetComponent<HealthComponent>();
	if( pHealthComp->HasEvent() ) return;
	
	const PlayerComponent* pPlayerComp = pObject->GetComponent<PlayerComponent>();


	switch ( pHealthComp->GetEvent() )
	{
		case HealthComponent::HealthEvent::LostHealth:
			std::cout << "Player " << (int) pPlayerComp->GetPlayerID() << " Has " << pHealthComp->GetRemainingLives() << " Lives Remaining." << std::endl;
			ServiceLocator::GetSoundService().PlaySound("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door1.wav", 50);

			break;
		case HealthComponent::HealthEvent::Died:
			std::cout << "Player " << (int) pPlayerComp->GetPlayerID() << " Died.\nBig Sad!" << std::endl;
			ServiceLocator::GetSoundService().PlaySound("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door2.wav", 50);
			break;
		default:
			break;
	}
	pHealthComp->EventHandeled();
}