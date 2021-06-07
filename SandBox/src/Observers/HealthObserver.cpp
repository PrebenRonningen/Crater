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
	if( !pObject->HasComponent<HealthComponent>() ) return;

	HealthComponent* pHealthComp = pObject->GetComponent<HealthComponent>();
	if( !pHealthComp->HasEvent() ) return;
	

	switch ( pHealthComp->GetEvent() )
	{
		case HealthComponent::HealthEvent::LostHealth:
			pHealthComp->LoseHealth(1);
			break;
		case HealthComponent::HealthEvent::Died:
			std::cout << "Dead\n";
		break;
		default:
			break;
	}

	pHealthComp->EventHandeled();
}