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
	if ( m_HealthComponent->GetRemainingLives() != m_PreviousHealth )
	{
		int currentHealth = m_HealthComponent->GetRemainingLives();
		CraterEngine::TextComponent* pTextComp = m_pParent->GetComponent<CraterEngine::TextComponent>();
		std::stringstream displayText;
		displayText << pTextComp->GetText();
		displayText << currentHealth;
		pTextComp->SetText(displayText.str());

		m_PreviousHealth = currentHealth;
	}
}
