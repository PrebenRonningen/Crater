#include "SandBoxPCH.h"
#include "CraterEngine.h"
#include "HealthDisplayComponent.h"
#include <sstream>

HealthDisplayComponent::HealthDisplayComponent(const CraterEngine::GameObject* parent, HealthComponent* healthComponent)
	: Component(parent)
	, m_HealthComponent{ healthComponent }
{
}

void HealthDisplayComponent::Update(const float)
{
	// should do this in the health observer
	if ( m_HealthComponent->GetRemainingLives() != m_PreviousHealth )
	{
		//int currentHealth = ;
		//CraterEngine::TextComponent* pTextComp = m_pParent->GetComponent<CraterEngine::TextComponent>();
		//std::stringstream displayText;
		//displayText << pTextComp->GetText();
		//displayText << currentHealth;
		//pTextComp->SetText(displayText.str());
	
		m_PreviousHealth = m_HealthComponent->GetRemainingLives();
	}
}

void HealthDisplayComponent::Render() const
{
	float padding = 1.25f;
	for ( int i{ 0 }; i < m_PreviousHealth; ++i )
	{
		m_pSprite->SetDestination(int(m_Position.x), int(m_Position.y + ( i * m_pSprite->GetTexInfo().destinationRectangle.h * padding)));
		m_pSprite->Render();
	}
}

bool HealthDisplayComponent::Initialize()
{
	if ( m_pParent->HasComponent<CraterEngine::SpriteComponent>() )
	{
		m_pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
		m_Position = m_pParent->GetComponent<CraterEngine::TransformComponent>()->GetPosition();
		return true;
	}
	return false;
}
