#include "SandBoxPCH.h"
#include "LevelObserver.h"
#include "Components/LevelComponent.h"
#include <CraterEngine.h>
#include "Components/MovementComponent.h"


LevelObserver::LevelObserver(LevelComponent* levelComponent)
	:m_Level(levelComponent)
{
	m_Level;
}

void LevelObserver::OnNotify(const CraterEngine::GameObject* pObject)
{
	if(pObject->HasComponent<MovementComponent>())
	{
		switch ( pObject->GetComponent<MovementComponent>()->GetEvent() )
		{
			case MovementComponent::MoveEvent::QbertLanded:
				std::cout << "Landed\n";
				pObject->GetComponent<MovementComponent>()->EventHandeled();
			break;
			case MovementComponent::MoveEvent::QbertJumpUp:
				std::cout << "Jump\n";
				pObject->GetComponent<MovementComponent>()->EventHandeled();
			break;
			default:
				break;
		}
	}

	switch ( m_Level->GetEvent())
	{
		case LevelComponent::LevelEvent::QbertLanded:
			m_Level->FlipCube(pObject->GetComponent<MovementComponent>()->GetCurrentPosition());
			m_Level->EventHandeled();
		break;
		case LevelComponent::LevelEvent::QbertJump:
			m_Level->PlayerLeftCube(pObject->GetComponent<MovementComponent>()->GetCurrentPosition());
		break;
		default:
			break;
	}
}

