#include "CraterPCH.h"
#include "CraterEngine.h"
#include "HealthObserver.h"
#include "Components/HealthComponent.h"
#include "Components/PlayerComponent.h"
#include <iostream>

void HealthObserver::OnNotify(const CraterEngine::GameObject& object, const CraterEngine::EventType& event)
{
	const HealthComponent& pHealthComp = *object.GetComponent<HealthComponent>();
	const PlayerComponent& pPlayerComp = *object.GetComponent<PlayerComponent>();
	switch ( event )
	{
		case CraterEngine::EventType::LostHealt:
			std::cout << "Player " << (int)pPlayerComp.GetPlayerID() << " Has " << pHealthComp.GetRemainingLives() << " Lives Remaining." << std::endl;
			break;
		case CraterEngine::EventType::Died:
			std::cout << "Player " << (int)pPlayerComp.GetPlayerID() <<" Died.\nBig Sad!" << std::endl;
			break;
		default:
			break;
	}
}

