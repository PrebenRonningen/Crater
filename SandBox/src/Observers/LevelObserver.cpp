#include "SandBoxPCH.h"
#include "LevelObserver.h"
#include "Components/LevelComponent.h"
#include <CraterEngine.h>


LevelObserver::LevelObserver(LevelComponent* levelComponent)
	:m_Level(levelComponent)
{
	m_Level;
}

void LevelObserver::OnNotify(const CraterEngine::GameObject* pObject)
{

	switch ( m_Level->GetEvent())
	{
		case LevelComponent::LevelEvent::QbertLanded:
			m_Level->FlipCube(pObject->GetComponent<CraterEngine::TransformComponent>()->GetPosition());
		break;
		default:
			break;
	}
	m_Level->EventHandeled();
}

