#include "SandBoxPCH.h"
#include "QbertComponent.h"
#include "LevelComponent.h"

QbertComponent::QbertComponent(const CraterEngine::GameObject* parent, LevelComponent* levelComponent)
	:Component(parent)
	, m_LevelComponent{ levelComponent }
{
}

bool QbertComponent::Initialize()
{
	m_LevelComponent->SetEvent(LevelComponent::LevelEvent::QbertLanded);
	m_pParent->Notify();
	return false;
}
