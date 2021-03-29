#include "CraterPCH.h"
#include "CraterEngine.h"
#include "HealthObserver.h"
#include "Components/HealthComponent.h"
#include "Components/PlayerComponent.h"
#include <iostream>
#include "Services/ServiceLocator.h"
#include "Services/Sound/SimpleSDL2AudioMaster.h"
#include "Services/Sound/LoggingSoundSystem.h"


void HealthObserver::OnNotify(const CraterEngine::GameObject& object, const CraterEngine::EventType& event)
{
	const HealthComponent& pHealthComp = *object.GetComponent<HealthComponent>();
	const PlayerComponent& pPlayerComp = *object.GetComponent<PlayerComponent>();
	switch ( event )
	{
		case CraterEngine::EventType::LostHealt:
			std::cout << "Player " << (int)pPlayerComp.GetPlayerID() << " Has " << pHealthComp.GetRemainingLives() << " Lives Remaining." << std::endl;
			ServiceLocator::GetSoundService().Play("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door1.wav", 50);
			break;
		case CraterEngine::EventType::Died:
			std::cout << "Player " << (int)pPlayerComp.GetPlayerID() <<" Died.\nBig Sad!" << std::endl;
			ServiceLocator::GetSoundService().Play("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door2.wav", 50);
			break;
		default:
			break;
	}
}